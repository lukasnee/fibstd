#include "fibutils/uptime.hpp"

namespace Fib::Utils
{
int Uptime::toString(std::uint64_t uptimeInMs, char *stringBufferOut, std::size_t stringBufferMaxSize)
{
    const decltype(uptimeInMs) millisecondsPerDay = 24 * 60 * 60 * 1000;
    const auto uptimeDays = uptimeInMs / millisecondsPerDay;
    const auto uptimeInSeconds = static_cast<std::time_t>(uptimeInMs / 1000);
    const auto uptimeMilliseconds = uptimeInMs % 1000;
    int charsPrinted = std::snprintf(stringBufferOut, stringBufferMaxSize, "%03lu:", uptimeDays);
    charsPrinted += static_cast<int>(std::strftime(stringBufferOut + charsPrinted, stringBufferMaxSize - charsPrinted,
                                                   "%T", std::gmtime(&uptimeInSeconds)));
    charsPrinted += std::snprintf(stringBufferOut + charsPrinted, stringBufferMaxSize - charsPrinted,
                                  ".%03lu:", uptimeMilliseconds);
    return charsPrinted;
}
} // namespace Fib::Utils