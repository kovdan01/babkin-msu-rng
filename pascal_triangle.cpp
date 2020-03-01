#include "pascal_triangle.h"
#include <cassert>

PascalTriangle::PascalTriangle(std::size_t size)
    : m_size(size)
    , m_binomials(std::vector<std::vector<std::uint64_t>>(m_size + 1))
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

std::uint64_t PascalTriangle::binomial(std::uint64_t n, std::uint64_t k) const
{
    if (n < k)
        return 0;
    assert(n <= m_size);
    assert(k >= 0);
    if (k < n / 2 + 1)
        return m_binomials[n][k];
    return m_binomials[n][n - k];
}
