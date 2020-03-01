#include "babkin.h"

std::ostream& operator<<(std::ostream& stream, const std::vector<std::uint8_t>& block)
{
    stream << "{ ";
    for (std::uint8_t elem : block)
        stream << static_cast<int>(elem) << ' ';
    stream << "}";
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Babkin<mpz_class>::CodePair& pair)
{
    stream << "{ k = " << pair.letter_count << ", b_k = " << pair.binomial_sum.get_str() << " }";
    return stream;
}
