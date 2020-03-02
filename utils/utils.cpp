#include "utils.h"
#include <fstream>

std::vector<std::uint8_t> compress_bits(const std::vector<std::uint8_t>& bits)
{
    std::vector<std::uint8_t> answer(bits.size() / 8, 0);
    for (std::size_t i = 0; i < bits.size(); i += 8)
    {
        const std::uint8_t* bit = bits.data() + i;
        std::uint8_t& current = answer[i / 8];
        for (int j = 7; j >= 0; --j, ++bit)
            current += (*bit << j);
    }
    return answer;
}

void write_to_file(const std::vector<std::uint8_t>& bytes, const std::string& filename)
{
    std::ofstream file(filename, std::ios_base::binary);
    for (std::uint8_t byte : bytes)
        file << byte;
}
