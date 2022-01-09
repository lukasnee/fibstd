/**
 * @ref https://github.com/bruxisma/byteswap
 *
 * Copyright 2018 Isabella Muerte
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <cstdint>
#include <type_traits>

namespace Fib::Std
{

namespace _byteswap
{
#define IXM_IS_CONSTEXPR(...) noexcept(is_constexpr(__VA_ARGS__))

template <class T> constexpr void is_constexpr(T &&t)
{
}

template <class T> constexpr auto as_unsigned(T value) noexcept
{
    return static_cast<std::make_unsigned_t<T>>(value);
}

#if defined(_MSC_VER)
inline auto bswap(std::uint64_t v) noexcept
{
    return _byteswap_uint64(v);
}
inline auto bswap(std::uint32_t v) noexcept
{
    return _byteswap_ulong(v);
}
inline auto bswap(std::uint16_t v) noexcept
{
    return _byteswap_ushort(v);
}

constexpr auto const_bswap(std::uint64_t v) noexcept
{
    return ((v & UINT64_C(0x0000'0000'0000'00FF)) << 56) | //
           ((v & UINT64_C(0x0000'0000'0000'FF00)) << 40) | //
           ((v & UINT64_C(0x0000'0000'00FF'0000)) << 24) | //
           ((v & UINT64_C(0x0000'0000'FF00'0000)) << 8) |  //
           ((v & UINT64_C(0x0000'00FF'0000'0000)) >> 8) |  //
           ((v & UINT64_C(0x0000'FF00'0000'0000)) >> 24) | //
           ((v & UINT64_C(0x00FF'0000'0000'0000)) >> 40) | //
           ((v & UINT64_C(0xFF00'0000'0000'0000)) >> 56);
}

constexpr auto const_bswap(std::uint32_t v) noexcept
{
    return ((v & UINT32_C(0x0000'00FF)) << 24) | //
           ((v & UINT32_C(0x0000'FF00)) << 8) |  //
           ((v & UINT32_C(0x00FF'0000)) >> 8) |  //
           ((v & UINT32_C(0xFF00'0000)) >> 24);
}

constexpr auto const_bswap(std::uint16_t v) noexcept
{
    return ((v & UINT16_C(0x00FF)) << 8) | ((v & UINT16_C(0xFF00)) >> 8);
}

#else
constexpr auto bswap(std::uint64_t v) noexcept
{
    return __builtin_bswap64(v);
}
constexpr auto bswap(std::uint32_t v) noexcept
{
    return __builtin_bswap32(v);
}
constexpr auto bswap(std::uint16_t v) noexcept
{
    return __builtin_bswap16(v);
}
#endif /* defined(_MSC_VER) */
} // namespace _byteswap

template <class IntegerType,
          class = std::enable_if_t<std::is_integral_v<IntegerType>>>
constexpr IntegerType byteswap(IntegerType value) noexcept
{
    if constexpr (sizeof(IntegerType) == 1)
    {
        return value;
    }
#if defined(_MSC_VER)
    if constexpr (IXM_IS_CONSTEXPR(value))
    {
        return _byteswap::const_bswap(_byteswap::as_unsigned(value));
    }
#endif /* defined(_MSC_VER) */
    return _byteswap::bswap(_byteswap::as_unsigned(value));
}
} // namespace Fib::Std