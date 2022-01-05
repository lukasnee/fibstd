

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_NO_POSIX_SIGNALS

#include <vector>

#include "catch.hpp"

#include "include/fibutils/prettyTable.hpp"
#include "include/fibutils/uptime.hpp"

TEST_CASE("prettyTable")
{
    struct User
    {
        const char *name;
        std::size_t age;
        const char *email;
        std::uint32_t registrationTimeStamp;
    };
    std::vector<User> userDataSet = {{{"John Cage", 22, "john.cage@bro.com", 1641399087},
                                      {"Chas Tenenbaum", 30, "chasychas@anderson.tv", 1641389087},
                                      {"Geralt of Rivia", 35, "Geralt69420@witchhub.lv", 1641397087}}};

    const char *title = "User list";
    const Fib::Utils::PrettyTable::ColumnsDescr<4> prettyTableColumnsDescr = {
        {{"name", "%s", 16},
         {"age", "%llu", 3},
         {"email", "%s", 24},
         {"is online for", "%s", Fib::Utils::Uptime::toStringBufferMinSize - 1}}};

    SECTION("PrettyTablePrinter")
    {
        Fib::Utils::PrettyTablePrinter prettyTablePrinter(std::printf, title, prettyTableColumnsDescr);
        for (auto &user : userDataSet)
        {
            std::array<char, Fib::Utils::Uptime::toStringBufferMinSize> stringBuffer;
            Fib::Utils::Uptime::toString(user.registrationTimeStamp, stringBuffer.data(), stringBuffer.size());
            REQUIRE(0 < prettyTablePrinter.printEntry(user.name, user.age, user.email, stringBuffer.data()));
        }
    }

    SECTION("PrettyTablePrinterTight")
    {
        Fib::Utils::PrettyTable prettyTable(std::printf, title, prettyTableColumnsDescr);
        prettyTable.config.noHorizontalLinesBetweenEntries = true;
        Fib::Utils::PrettyTablePrinter prettyTablePrinter(prettyTable);

        for (auto &user : userDataSet)
        {
            std::array<char, Fib::Utils::Uptime::toStringBufferMinSize> stringBuffer;
            Fib::Utils::Uptime::toString(user.registrationTimeStamp, stringBuffer.data(), stringBuffer.size());
            REQUIRE(0 < prettyTablePrinter.printEntry(user.name, user.age, user.email, stringBuffer.data()));
        }
    }
}
