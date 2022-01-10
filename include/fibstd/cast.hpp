#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace Fib::Std
{
namespace Cast
{
/** @note may be replace with std::to_underlying since C++23 */

template <typename Enum> static constexpr std::underlying_type_t<Enum> toUnderlying(const Enum &e)
{
    return static_cast<std::underlying_type_t<Enum>>(e);
}

template <typename Enum> static constexpr Enum toEnum(const std::underlying_type_t<Enum> &value)
{
    return static_cast<Enum>(value);
}
} // namespace Cast
} // namespace Fib::Std