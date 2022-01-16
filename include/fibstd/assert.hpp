#pragma once

#include <cstdint>
#include <cstring>

namespace Fib::Std
{
struct AssertInfo
{
    char fileline[256];
};

extern AssertInfo assertInfo;

void fibstd_assert(const char *file, std::uint32_t line);

constexpr const char *file_name(const char *path)
{
    const char *file = path;
    while (*path)
    {
        if (*path++ == '/')
        {
            file = path;
        }
    }
    return file;
}
} // namespace Fib::Std

#define FIBSTD_ASSERT(expr)                                                                                            \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(expr))                                                                                                   \
        {                                                                                                              \
            Fib::Std::fibstd_assert(Fib::Std::file_name(__FILE__), __LINE__);                                          \
        }                                                                                                              \
    } while (0)
