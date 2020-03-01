#ifndef PASCAL_TRIANGLE_H
#define PASCAL_TRIANGLE_H

#include <cstdint>
#include <vector>

class PascalTriangle
{
public:
    PascalTriangle() = delete;
    PascalTriangle(std::size_t size);
    PascalTriangle(const PascalTriangle&) = default;
    PascalTriangle& operator=(const PascalTriangle&) = default;
    PascalTriangle(PascalTriangle&&) noexcept = default;
    PascalTriangle& operator=(PascalTriangle&&) noexcept = default;

    [[nodiscard]] std::uint64_t binomial(std::uint64_t n, std::uint64_t k) const;

private:
    std::size_t m_size;
    std::vector<std::vector<std::uint64_t>> m_binomials;
};

#endif // PASCAL_TRIANGLE_H
