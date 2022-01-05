#pragma once

#include <algorithm>
#include <cstdint>
#include <cstddef>

namespace Fib::Utils
{
template <typename T> T swapEndian(const T &val)
{
    union U
    {
        T val;
        std::array<std::uint8_t, sizeof(T)> raw;
    } src, dst;

    src.val = val;
    std::reverse_copy(src.raw.begin(), src.raw.end(), dst.raw.begin());
    return dst.val;
}

/** @note optimized */
template <> std::uint32_t swapEndian(const std::uint32_t &value)
{
    std::uint32_t tmp = ((value << 8) & 0xFF00FF00) | ((value >> 8) & 0xFF00FF);
    return ((tmp << 16) | (tmp >> 16));
}
} // namespace Fib::Utils