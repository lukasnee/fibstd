/**
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
 *
 * @ref https://github.com/bruxisma/byteswap
 *
 * @note Stripped down by Lukas Neverauskis.
 */

#pragma once

#include <cstdint>
#include <type_traits>

namespace Fib::Std
{

template <class T> constexpr auto as_unsigned(T value) noexcept
{
    return static_cast<std::make_unsigned_t<T>>(value);
}

constexpr auto _byteswap(std::uint64_t v) noexcept
{
    return __builtin_bswap64(v);
}
constexpr auto _byteswap(std::uint32_t v) noexcept
{
    return __builtin_bswap32(v);
}
constexpr auto _byteswap(std::uint16_t v) noexcept
{
    return __builtin_bswap16(v);
}

template <class IntegerType, class = std::enable_if_t<std::is_integral_v<IntegerType>>>
constexpr IntegerType byteswap(IntegerType value) noexcept
{
    if constexpr (sizeof(IntegerType) == 1)
    {
        return value;
    }
    else
    {
        return _byteswap(as_unsigned(value));
    }
}
} // namespace Fib::Std