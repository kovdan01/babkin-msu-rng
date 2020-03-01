#include "babkin.h"
#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <map>

Babkin::NBlock generate_block(std::size_t size, double one_probability = 0.5)
{
    static std::uniform_real_distribution<double> dist(0, 1);
    static std::mt19937 prng(std::random_device{}());

    Babkin::NBlock answer(size);
    for (std::uint8_t& elem : answer)
        elem = (dist(prng) < one_probability);

    return answer;
}

int main()
{
    std::size_t block_size = 64;
    std::cout << "Start babkin creation...\n";
    Babkin babkin(block_size);
    std::cout << "Finish babkin creation!\n";

    std::cout << "Start generating blocks...\n";
    std::map<int, std::vector<Babkin::NBlock>> percentage_to_blocks;
    for (int percentage = 10; percentage < 100; percentage += 10)
    {
        std::size_t blocks_count = 10'000;
        percentage_to_blocks[percentage] = std::vector<Babkin::NBlock>(blocks_count);
        for (Babkin::NBlock& block : percentage_to_blocks[percentage])
            block = generate_block(block_size, percentage / 100.0);
    }
    std::cout << "Finish generating blocks\n";

    for (auto& [percentage, blocks] : percentage_to_blocks)
    {
        std::vector<std::uint8_t> cumulative;
        using namespace std::chrono;
        time_point<high_resolution_clock> begin, end;
        std::int64_t time = 0;
        for (const Babkin::NBlock& block : blocks)
        {
            begin = high_resolution_clock::now();
            Babkin::CodeBlock code_block = babkin.get_random_block(block);
            end = high_resolution_clock::now();
            time += duration_cast<nanoseconds>(end - begin).count();
#ifndef NDEBUG
            Babkin::CodePair code_pair = babkin.encode(block);
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
                  << "remaining data proportion is " << std::setw(8) << remaining_data_proportion << '\n';
    }
}
