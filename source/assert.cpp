#include "fibstd/assert.hpp"

#include <cstdio>
#include <cstring>

namespace Fib::Std
{
AssertInfo assertInfo;

#define ansiColorReset "\e[0m"
#define ansiColorRed "\e[0;31m"

void fibstd_assert(const char *file, std::uint32_t line)
{
    std::snprintf(assertInfo.fileline, sizeof(assertInfo.fileline),
                  ansiColorRed "assert fail at: " ansiColorReset "%s:%u", file, line);
    // std::puts(assertInfo.fileline);
    // __asm("bkpt 3");
}
} // namespace Fib::Std