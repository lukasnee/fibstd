#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <ctime>

namespace Fib::Std
{
namespace Uptime
{
/** @brief formats into "DDD:HH:MM:SS.mmm" */
int toString(std::uint64_t uptimeInMs, char *stringBufferOut, std::size_t stringBufferMaxSize);

constexpr int toStringBufferMinSize = sizeof("DDD:HH:MM:SS.mmm");
constexpr int toStringFmtLength = toStringBufferMinSize - sizeof('\0');
} // namespace Uptime
} // namespace Fib::Std