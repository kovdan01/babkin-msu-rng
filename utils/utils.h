#ifndef UTILS_H
#define UTILS_H

#include "babkin.h"
#include <vector>
#include <cstdint>
#include <string>
#include <random>

template <typename Integer>
typename Babkin<Integer>::NBlock generate_block(std::size_t size, double one_probability = 0.5)
{
    static std::uniform_real_distribution<double> dist(0, 1);
    static std::mt19937 prng(std::random_device{}());

    typename Babkin<Integer>::NBlock answer(size);
    for (std::uint8_t& elem : answer)
        elem = (dist(prng) < one_probability);

    return answer;
}

std::vector<std::uint8_t> compress_bits(const std::vector<std::uint8_t>& bits);

void write_to_file(const std::vector<std::uint8_t>& bytes, const std::string& filename);


#endif // UTILS_H
