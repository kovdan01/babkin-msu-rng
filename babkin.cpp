#include "babkin.h"
#include <cassert>

Babkin::Babkin(std::size_t block_size)
    : m_block_size(block_size)
    , m_pascal_triangle(m_block_size)
{
}

std::size_t Babkin::block_size() const
{
    return m_block_size;
}

Babkin::CodePair Babkin::encode(const Babkin::NBlock& input) const
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

Babkin::CodeBlock Babkin::get_random_block(const NBlock &input) const
{
    return get_random_block(encode(input));
}

Babkin::CodeBlock Babkin::get_random_block(const CodePair &pair) const
{
    std::uint64_t block_class_size = m_pascal_triangle.binomial(m_block_size, pair.letter_count);
    std::uint8_t binomial_max_bit = 0;
    for (std::uint64_t mask = 0b1; pair.binomial_sum + 1 > (block_class_size & mask); mask <<= 1, mask |= 1)
        ++binomial_max_bit;

    Babkin::CodeBlock answer(binomial_max_bit + 1);
    std::uint64_t binomial_bit_mask = (std::uint64_t{1} << binomial_max_bit);
    for (std::size_t i = 0; i != answer.size(); ++i, binomial_bit_mask >>= 1)
        answer[i] = static_cast<bool>(pair.binomial_sum & binomial_bit_mask);

    return answer;
}

std::ostream& operator<<(std::ostream& stream, const Babkin::CodeBlock& block)
{
    stream << "{ ";
    for (std::uint8_t elem : block)
        stream << static_cast<int>(elem) << ' ';
    stream << "}";
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Babkin::CodePair& pair)
{
    stream << "{ k = " << pair.letter_count << ", b_k = " << pair.binomial_sum << " }";
    return stream;
}

// unused
// std::uint8_t Babkin::find_max_bit(std::uint64_t x)
// {
//     std::uint8_t t = 0;
//     std::uint64_t one = 1;
//     if (x >= (one << t) << 32) t += 32;
//     if (x >= (one << t) << 16) t += 16;
//     if (x >= (one << t) <<  8) t +=  8;
//     if (x >= (one << t) <<  4) t +=  4;
//     if (x >= (one << t) <<  2) t +=  2;
//     if (x >= (one << t) <<  1) t +=  1;

//     return t;
// }
