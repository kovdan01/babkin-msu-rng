#ifndef PASCAL_TRIANGLE_H
#define PASCAL_TRIANGLE_H

#include <cstdint>
#include <vector>
#include <cassert>

template <typename Integer>
class PascalTriangle
{
public:
    // constructors
    PascalTriangle() = delete;
    PascalTriangle(const PascalTriangle&) = default;
    PascalTriangle& operator=(const PascalTriangle&) = default;
    PascalTriangle(PascalTriangle&&) noexcept = default;
    PascalTriangle& operator=(PascalTriangle&&) noexcept = default;

    PascalTriangle(std::size_t size)
        : m_size(size)
        , m_binomials(std::vector<std::vector<Integer>>(m_size + 1))
    {
        m_binomials[0] = { 1 };
        for (std::size_t n = 1; n <= m_size; ++n)
        {
            m_binomials[n].resize(n / 2 + 1);
            m_binomials[n][0] = 1;
            for (std::size_t k = 1; k < m_binomials[n].size(); ++k)
                m_binomials[n][k] = m_binomials[n - 1][k - 1] + binomial(n - 1, k);
        }
    }

    // member functions
    [[nodiscard]] const Integer& binomial(std::uint64_t n, std::uint64_t k) const
    {
        if (n < k)
            return m_zero;
        assert(n <= m_size);
        assert(k >= 0);
        if (k < n / 2 + 1)
            return m_binomials[n][k];
        return m_binomials[n][n - k];
    }

private:
    std::size_t m_size;
    std::vector<std::vector<Integer>> m_binomials;
    inline static Integer m_zero = 0;
};

#endif // PASCAL_TRIANGLE_H
