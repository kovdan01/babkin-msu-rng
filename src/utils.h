#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <cstdint>
#include <string>

std::vector<std::uint8_t> compress_bits(const std::vector<std::uint8_t> bits);

void write_to_file(const std::vector<std::uint8_t> bytes, const std::string& filename);


#endif // UTILS_H
