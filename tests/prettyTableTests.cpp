#define CATCH_CONFIG_NO_POSIX_SIGNALS

#include "catch.hpp"

#include "fibutils/prettyTable.hpp"
#include "fibutils/uptime.hpp"

#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <vector>

#define DEBUG

int customPrintf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
#ifdef DEBUG
    int result = std::vprintf(fmt, args);
#else
    std::array<char, 1> stringBuffer;
    int result = std::vsnprintf(stringBuffer.data(), stringBuffer.size(), fmt, args);
#endif
    va_end(args);
    return result;
}

TEST_CASE("prettyTable")
{
    struct User
    {
        const char *name;
        std::size_t age;
        double height;
        const char *email;
        std::uint32_t registrationTimeStamp;
    };
    std::vector<User> userDataSet = {{{"John Cage", 22, 1.23, "john.cage@bro.com", 1641399087},
                                      {"Chas Tenenbaum", 30, 1.70, "chasychas@anderson.tv", 1641389087},
                                      {"Geralt of Rivia", 35, 1.87, "Geralt69420@witchhub.lv", 1641397087}}};

    const char *title = "User list";
    const Fib::Utils::PrettyTable::ColumnsDescr<5> prettyTableColumnsDescr = {
        {{"name", "%s", 16},
         {"age", "%3llu", 3},
         {"height", "%4.2f m", 6},
         {"email", "%s", 24},
         {"is online for", "%s", Fib::Utils::Uptime::toStringBufferMinSize - 1}}};

    SECTION("PrettyTablePrinter")
    {
        Fib::Utils::PrettyTablePrinter prettyTablePrinter(customPrintf, title, prettyTableColumnsDescr);
        for (auto &user : userDataSet)
        {
            std::array<char, Fib::Utils::Uptime::toStringBufferMinSize> stringBuffer;
            Fib::Utils::Uptime::toString(user.registrationTimeStamp, stringBuffer.data(), stringBuffer.size());
            REQUIRE(0 <
                    prettyTablePrinter.printEntry(user.name, user.age, user.height, user.email, stringBuffer.data()));
        }
    };

    SECTION("PrettyTablePrinterTight")
    {
        Fib::Utils::PrettyTable prettyTable(customPrintf, title, prettyTableColumnsDescr);
        prettyTable.config.noHorizontalLinesBetweenEntries.set(true);
        Fib::Utils::PrettyTablePrinter prettyTablePrinter(prettyTable);

        for (auto &user : userDataSet)
        {
            std::array<char, Fib::Utils::Uptime::toStringBufferMinSize> stringBuffer;
            Fib::Utils::Uptime::toString(user.registrationTimeStamp, stringBuffer.data(), stringBuffer.size());
            REQUIRE(0 <
                    prettyTablePrinter.printEntry(user.name, user.age, user.height, user.email, stringBuffer.data()));
        }
    }
}
