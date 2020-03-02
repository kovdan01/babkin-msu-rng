#include "babkin.h"
#include "utils.h"
#include <gmpxx.h>
#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <map>

using BabkinLong = Babkin<mpz_class>;

int main()
{
    std::size_t block_size = (1 << 12);
    std::cout << "Start babkin creation...\n";
    BabkinLong babkin(block_size);
    std::cout << "Finish babkin creation!\n";

    int percentage = 20;
    std::size_t blocks_count = 10'000;

    std::cout << "Start generating data...\n";
    std::vector<std::uint8_t> cumulative;
    for (std::size_t i = 0; i < blocks_count; ++i)
    {
        if (i % 1'000 == 0)
            std::cout << "Generating data from block " << i << "...\n";
        BabkinLong::NBlock block = generate_block<mpz_class>(block_size, percentage / 100.0);
        BabkinLong::CodeBlock code_block = babkin.get_random_block(block);
        std::copy(code_block.begin(), code_block.end(), std::back_inserter(cumulative));
    }
    std::cout << "Finish generating data\n";

    std::cout << "Start writing to file...\n";
    write_to_file(compress_bits(cumulative), "data.bin");
    std::cout << "Finish writing to file\n";
}
