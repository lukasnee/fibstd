#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace Fib::Utils
{
template <typename Enum> static constexpr std::underlying_type_t<Enum> enumToValue(const Enum &e)
{
    return static_cast<std::underlying_type_t<Enum>>(e);
}

template <typename Enum> static constexpr Enum valueToEnum(const std::underlying_type_t<Enum> &value)
{
    return static_cast<Enum>(value);
}
} // namespace Fib::Utils