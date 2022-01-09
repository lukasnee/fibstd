#define CATCH_CONFIG_NO_POSIX_SIGNALS

#include "catch.hpp"

#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include "fibstd/configVariable.hpp"

class Zoo
{
public:
#define CONFIG_VARS                                                                                                    \
    CONFIG_VAR(const char *, name, "Harambe")                                                                          \
    CONFIG_VAR(std::size_t, strength, 9001)                                                                            \
    CONFIG_VAR(double, charisma, 100.00)
#include "fibstd/configTemplate.hpp"
#undef CONFIG_VARS
};

TEST_CASE("configTemplateDefault")
{
    Zoo zoo;

    SECTION("1")
    {
        REQUIRE(0 == std::strcmp(zoo.config.name.get(), "Harambe"));
    }

    SECTION("2")
    {
        REQUIRE(zoo.config.strength.get() == 9001);
    }

    SECTION("3")
    {
        REQUIRE(zoo.config.charisma.get() == 100.00);
    }
}

TEST_CASE("configTemplateSetNewValue")
{
    Zoo zoo;

    SECTION("1")
    {
        constexpr auto newValue = nullptr;
        zoo.config.name.set(newValue);
        REQUIRE(zoo.config.name.get() == newValue);
    }

    SECTION("2")
    {
        constexpr auto newValue = 42;
        zoo.config.strength.set(newValue);
        REQUIRE(zoo.config.strength.get() == newValue);
    }

    SECTION("3")
    {
        constexpr auto newValue = 123.456;
        zoo.config.charisma.set(newValue);
        REQUIRE(zoo.config.charisma.get() == newValue);
    }
}
