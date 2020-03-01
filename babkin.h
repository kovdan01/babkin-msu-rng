#ifndef BABKIN_H
#define BABKIN_H

#include "pascal_triangle.h"
#include <cstdint>
#include <vector>
#include <ostream>

class Babkin
{
public:
    Babkin() = delete;
    Babkin(std::size_t block_size);
    Babkin(const Babkin&) = default;
    Babkin& operator=(const Babkin&) = default;
    Babkin(Babkin&&) noexcept = default;
    Babkin& operator=(Babkin&&) noexcept = default;

    [[nodiscard]] std::size_t block_size() const;

    using NBlock = std::vector<std::uint8_t>;
    using CodeBlock = std::vector<std::uint8_t>;
    struct CodePair
    {
        std::uint64_t letter_count;
        std::uint64_t binomial_sum;
    };

    [[nodiscard]] CodePair encode(const NBlock& input) const;
    [[nodiscard]] CodeBlock get_random_block(const NBlock& input) const;
    [[nodiscard]] CodeBlock get_random_block(const CodePair& pair) const;

private:
    std::size_t m_block_size;
    PascalTriangle m_pascal_triangle;

    // unused
    // static std::uint8_t find_max_bit(std::uint64_t x);
};

std::ostream& operator<<(std::ostream& stream, const Babkin::CodeBlock& block);
std::ostream& operator<<(std::ostream& stream, const Babkin::CodePair& pair);

#endif // BABKIN_H
