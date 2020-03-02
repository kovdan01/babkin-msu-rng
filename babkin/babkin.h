#ifndef BABKIN_H
#define BABKIN_H

#include "pascal_triangle.h"
#include <gmpxx.h>
#include <cstdint>
#include <vector>
#include <ostream>
#include <cassert>
#include <tuple>

template <typename Integer>
class Babkin
{
public:
    // constructors
    Babkin() = delete;
    Babkin(const Babkin&) = default;
    Babkin& operator=(const Babkin&) = default;
    Babkin(Babkin&&) noexcept = default;
    Babkin& operator=(Babkin&&) noexcept = default;

    Babkin(std::size_t block_size)
        : m_block_size(block_size)
        , m_pascal_triangle(m_block_size)
    {
    }

    // getters
    [[nodiscard]] std::size_t block_size() const
    {
        return m_block_size;
    }

    // member types
    using NBlock = std::vector<std::uint8_t>;
    using CodeBlock = std::vector<std::uint8_t>;
    struct CodePair
    {
        std::uint64_t letter_count;
        Integer binomial_sum;
    };

    friend bool operator==(const CodePair& lhs, const CodePair& rhs)
    {
        return std::tie(lhs.letter_count, lhs.binomial_sum) == std::tie(rhs.letter_count, rhs.binomial_sum);
    }

    // member functions
    [[nodiscard]] CodePair encode(const NBlock& input) const
    {
        assert(input.size() == m_block_size);

        std::size_t ones_count = 0;
        for (std::uint8_t elem : input)
            ones_count += static_cast<bool>(elem);

        bool letter = (ones_count <= m_block_size / 2);

        Babkin::CodePair answer =
        {
            (letter ? ones_count : m_block_size - ones_count),
            0
        };

        for (std::size_t i = 0, letter_num = 1; i < m_block_size; ++i)
            if (static_cast<bool>(input[i]) == letter)
                answer.binomial_sum += m_pascal_triangle.binomial(i, letter_num++);

        return answer;
    }

    [[nodiscard]] CodeBlock get_random_block(const NBlock& input) const
    {
        return get_random_block(encode(input));
    }

    [[nodiscard]] CodeBlock get_random_block(const CodePair& pair) const
    {
        Integer block_class_size = m_pascal_triangle.binomial(m_block_size, pair.letter_count);
        std::uint64_t binomial_max_bit = 0;
        for (Integer mask = 0b1; pair.binomial_sum + 1 > (block_class_size & mask); mask <<= 1, mask |= 1)
            ++binomial_max_bit;

        Babkin::CodeBlock answer(binomial_max_bit + 1);
        Integer binomial_bit_mask = (Integer{1} << binomial_max_bit);
        for (std::size_t i = 0; i != answer.size(); ++i, binomial_bit_mask >>= 1)
            answer[i] = ((pair.binomial_sum & binomial_bit_mask) != 0);

        return answer;
    }

private:
    std::size_t m_block_size;
    PascalTriangle<Integer> m_pascal_triangle;
};

std::ostream& operator<<(std::ostream& stream, const std::vector<std::uint8_t>& block);

template <typename Integer>
std::ostream& operator<<(std::ostream& stream, const typename Babkin<Integer>::CodePair& pair)
{
    stream << "{ k = " << pair.letter_count << ", b_k = " << pair.binomial_sum << " }";
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Babkin<mpz_class>::CodePair& pair);

#endif // BABKIN_H
