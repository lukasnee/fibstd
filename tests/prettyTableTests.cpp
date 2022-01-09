#define CATCH_CONFIG_NO_POSIX_SIGNALS

#include "catch.hpp"

#include "fibstd/prettyTable.hpp"
#include "fibstd/uptime.hpp"

#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

std::array<char, 1024 * 1024> stringBufferTmp;
std::string actualOutput;
int customPrintf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int result = std::vsnprintf(stringBufferTmp.data(), stringBufferTmp.size(), fmt, args);
    if (result > 0)
    {
        actualOutput.append(stringBufferTmp.data());
        // printf("%s", stringBufferTmp.data());
        // std::puts(stringBufferTmp.data()); // useful - nicely displays individual prints
    }
    va_end(args);
    return result;
}

TEST_CASE("prettyTable")
{
    actualOutput.clear();

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
    const Fib::Std::PrettyTable::ColumnsDescr<5> prettyTableColumnsDescr = {
        {{"name", "%s", 16},
         {"age", "%3llu", 3},
         {"height", "%4.2f m", 6},
         {"email", "%s", 24},
         {"is online for", "%s", Fib::Std::Uptime::toStringBufferMinSize - 1}}};

    SECTION("PrettyTablePrinter")
    {
        {
            Fib::Std::PrettyTablePrinter prettyTablePrinter(customPrintf, title, prettyTableColumnsDescr);
            for (auto &user : userDataSet)
            {
                std::array<char, Fib::Std::Uptime::toStringBufferMinSize> stringBuffer;
                Fib::Std::Uptime::toString(user.registrationTimeStamp, stringBuffer.data(), stringBuffer.size());
                prettyTablePrinter.printEntry(user.name, user.age, user.height, user.email, stringBuffer.data());
            }
        }

        const char *expectedOutput =
            "+-------------------------------------------------------------------------------+\n"
            "| User list                                                                     |\n"
            "+------------------+-----+--------+--------------------------+------------------+\n"
            "| name             | age | height | email                    | is online for    |\n"
            "+------------------+-----+--------+--------------------------+------------------+\n"
            "| John Cage        |  22 | 1.23 m | john.cage@bro.com        | 018:23:56:39.087 |\n"
            "+------------------+-----+--------+--------------------------+------------------+\n"
            "| Chas Tenenbaum   |  30 | 1.70 m | chasychas@anderson.tv    | 018:23:56:29.087 |\n"
            "+------------------+-----+--------+--------------------------+------------------+\n"
            "| Geralt of Rivia  |  35 | 1.87 m | Geralt69420@witchhub.lv  | 018:23:56:37.087 |\n"
            "+------------------+-----+--------+--------------------------+------------------+\n";
        REQUIRE(actualOutput.size() == std::strlen(expectedOutput));
        REQUIRE_THAT(actualOutput.c_str(), Catch::Equals(expectedOutput));
    };

    SECTION("PrettyTablePrinterTight")
    {
        {
            Fib::Std::PrettyTable prettyTable(customPrintf, title, prettyTableColumnsDescr);
            prettyTable.config.noHorizontalLinesBetweenEntries.set(true);
            Fib::Std::PrettyTablePrinter prettyTablePrinter(prettyTable);

            for (auto &user : userDataSet)
            {
                std::array<char, Fib::Std::Uptime::toStringBufferMinSize> stringBuffer;
                Fib::Std::Uptime::toString(user.registrationTimeStamp, stringBuffer.data(), stringBuffer.size());
                prettyTablePrinter.printEntry(user.name, user.age, user.height, user.email, stringBuffer.data());
            }
        }

        const char *expectedOutput =
            "+-------------------------------------------------------------------------------+\n"
            "| User list                                                                     |\n"
            "+------------------+-----+--------+--------------------------+------------------+\n"
            "| name             | age | height | email                    | is online for    |\n"
            "+------------------+-----+--------+--------------------------+------------------+\n"
            "| John Cage        |  22 | 1.23 m | john.cage@bro.com        | 018:23:56:39.087 |\n"
            "| Chas Tenenbaum   |  30 | 1.70 m | chasychas@anderson.tv    | 018:23:56:29.087 |\n"
            "| Geralt of Rivia  |  35 | 1.87 m | Geralt69420@witchhub.lv  | 018:23:56:37.087 |\n"
            "+------------------+-----+--------+--------------------------+------------------+\n";
        REQUIRE(actualOutput.size() == std::strlen(expectedOutput));
        REQUIRE_THAT(actualOutput.c_str(), Catch::Equals(expectedOutput));
    }
    actualOutput.clear();
}
