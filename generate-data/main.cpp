#include "babkin.h"
#include "utils.h"

#include <gmpxx.h>
#include <boost/program_options.hpp>

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cmath>

template <typename Integer>
void job(std::size_t block_size, std::size_t blocks_count, double probability, const std::string& output_filename)
{
    std::cout << "Start babkin creation..." << std::endl;
    Babkin<Integer> babkin(block_size);
    std::cout << "Finish babkin creation!" << std::endl;

    std::cout << "Start generating data..." << std::endl;
    std::vector<std::uint8_t> cumulative;
    std::size_t output_interval = static_cast<std::size_t>(5'000'000'000 / std::pow(std::log(block_size), 7)); // strange heuristic, don't try to understand it
    for (std::size_t i = 0; i < blocks_count; ++i)
    {
        if (i % output_interval == 0 || i + 1 == blocks_count)
            std::cout << "[ " << std::internal << std::setprecision(2) << std::fixed << std::setw(6)
                      << 100.0 * i / blocks_count << "% ] Generating data from block " << i << "..." << std::endl;
        typename Babkin<Integer>::NBlock block = generate_block<mpz_class>(block_size, probability);
        typename Babkin<Integer>::CodeBlock code_block = babkin.get_random_block(block);
        std::copy(code_block.begin(), code_block.end(), std::back_inserter(cumulative));
    }
    std::cout << "Finish generating data" << std::endl;

    std::cout << "Start writing to file..." << std::endl;
    write_bytes_to_file(compress_bits(cumulative), output_filename);
    std::cout << "Finish writing to file" << std::endl;
}

int main(int argc, char* argv[]) try
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,H",                                                        "Print this message")
        ("size,S",        po::value<std::size_t>()->default_value(64),    "Block size for the input of Babkin's algorithm. "
                                                                          "Long arithmetics will be used if it is more than 64, "
                                                                          "that will lead to perfomance decrease")
        ("count,C",       po::value<std::size_t>()->default_value(1'000), "Number of blocks to be generated and processed")
        ("probability,P", po::value<double>()->default_value(0.5),        "Parameter of Bernoulli distribution "
                                                                          "proportion of '1' in bit sequence")
        ("output,O",      po::value<std::string>()->required(),           "Name of output file")
        ;

    po::variables_map vm;
    try
    {
        po::store(parse_command_line(argc, argv, desc), vm);
        if (vm.contains("help"))
        {
            std::cout << "This program generates data to be tested with NIST statistical test suite.\n"
                         "Steps:\n"
                         " - The program generates bit sequence with Bernoulli distribuion.\n"
                         "   The sequence contains <count> bit blocks of <size> length.\n"
                         " - Then this sequence is treated as an input for Babkin's algorithm,\n"
                         "   and its output is stored to <output> file\n\n"
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
    double probability = vm["probability"].as<double>();
    std::string output_filename = vm["output"].as<std::string>();

    if (block_size > 64)
        job<mpz_class>(block_size, blocks_count, probability, output_filename);
    else
        job<std::uint64_t>(block_size, blocks_count, probability, output_filename);
}
catch (const std::exception& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
