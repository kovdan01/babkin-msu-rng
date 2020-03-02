#include "babkin.h"
#include "utils.h"

#include <gmpxx.h>
#include <boost/program_options.hpp>

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <map>
#include <stdexcept>

template <typename Integer>
void test(std::size_t block_size, std::size_t blocks_count)
{
    std::cout << "Start babkin creation..." << std::endl;
    Babkin<Integer> babkin(block_size);
    std::cout << "Finish babkin creation!" << std::endl;

    std::cout << "Start generating blocks..." << std::endl;
    std::map<int, std::vector<typename Babkin<Integer>::NBlock>> percentage_to_blocks;
    for (int percentage = 10; percentage < 100; percentage += 10)
    {
        percentage_to_blocks[percentage] = std::vector<typename Babkin<Integer>::NBlock>(blocks_count);
        for (typename Babkin<Integer>::NBlock& block : percentage_to_blocks[percentage])
            block = generate_block<mpz_class>(block_size, percentage / 100.0);
    }
    std::cout << "Finish generating blocks" << std::endl;

    for (auto& [percentage, blocks] : percentage_to_blocks)
    {
        std::vector<std::uint8_t> cumulative;
        using namespace std::chrono;
        time_point<high_resolution_clock> begin, end;
        std::int64_t time = 0;
        for (const typename Babkin<Integer>::NBlock& block : blocks)
        {
            begin = high_resolution_clock::now();
            typename Babkin<Integer>::CodeBlock code_block = babkin.get_random_block(block);
            end = high_resolution_clock::now();
            time += duration_cast<nanoseconds>(end - begin).count();
#ifndef NDEBUG
            Babkin<Integer>::CodePair code_pair = babkin.encode(block);
            std::cerr << "     " << block << "\n --> " << code_pair << "\n --> " << code_block << '\n';
#endif
            std::copy(code_block.begin(), code_block.end(), std::back_inserter(cumulative));
        }

        double ones_proportion = 1.0 * std::accumulate(cumulative.begin(), cumulative.end(), 0) / cumulative.size();
        double output_speed = cumulative.size() * 1'000.0 / time;
        double remaining_data_proportion = 1.0 * cumulative.size() / (block_size * blocks.size());
        std::cout << percentage << "% of ones: "
                  << "output ones proportion is "    << std::setw(8) << ones_proportion << ", "
                  << "output speed is "              << std::setw(7) << output_speed << " Mbit/s, "
                  << "remaining data proportion is " << std::setw(8) << remaining_data_proportion << std::endl;
    }
}

int main(int argc, char* argv[]) try
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,H",                                                  "Print this message")
        ("size,S",  po::value<std::size_t>()->default_value(64),    "Block size for the input of Babkin's algorithm. "
                                                                    "Long arithmetics will be used if it is more than 64, "
                                                                    "that will lead to perfomance decrease")
        ("count,C", po::value<std::size_t>()->default_value(1'000), "Number of blocks to be generated and processed")
        ;

    po::variables_map vm;
    try
    {
        po::store(parse_command_line(argc, argv, desc), vm);
        if (vm.contains("help"))
        {
            std::cout << "This program checks the following characteristics of the alogrithm:\n"
                         " - proportion of '1' in output sequence\n"
                         " - output sequence generation speed\n"
                         " - proportion of remaining data (the ratio of input and output sequences length)\n"
                         "All checks are made for input sequences of bits that have Bernoulli distribution\n"
                         "with parameters (0.1, 0.9), (0.2, 0.8), ..., (0.9, 0.1).\n\n"
                      << desc << '\n';
            return 0;
        }
        po::notify(vm);
    }
    catch (const po::error& error)
    {
        std::cerr << "Error while parsing command-line arguments: "
                  << error.what() << "\nPlease use --help to see help message\n";
        return 1;
    }

    std::size_t block_size = vm["size"].as<std::size_t>();
    std::size_t blocks_count = vm["count"].as<std::size_t>();

    if (block_size > 64)
        test<mpz_class>(block_size, blocks_count);
    else
        test<std::uint64_t>(block_size, blocks_count);
}
catch (const std::exception& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
