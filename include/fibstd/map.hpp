#pragma once

#include "fibstd/assert.hpp"

#include <array>
#include <cassert>
// #include <stdexcept>
// #include <algorithm>

namespace Fib::Std
{
/** @brief constexpr enabled map - fast ! */
template <typename Key, typename Value, std::size_t Size> struct Map
{
    static constexpr Value notFound = {};
    std::array<std::pair<Key, Value>, Size> data;

    template <class InputIt, class T> constexpr InputIt find(InputIt first, InputIt last, const T &value) const
    {
        for (; first != last; ++first)
        {
            if (*first == value)
            {
                return first;
            }
        }
        return last;
    }

    template <class InputIt, class UnaryPredicate>
    constexpr InputIt find_if(InputIt first, InputIt last, UnaryPredicate p) const
    {
        for (; first != last; ++first)
        {
            if (p(*first))
            {
                return first;
            }
        }
        return last;
    }

    [[nodiscard]] constexpr Value at(const Key &key) const
    {
        /** @note there's constexpr std::find_if since C++20 */
        const auto it = find_if(data.begin(), data.end(), [&key](const auto &value) { return value.first == key; });
        if (it != std::end(data))
        {
            return it->second;
        }
        else
        {
            // throw std::range_error("Not Found");
            return notFound;
        }
    }
};
} // namespace Fib::Std
