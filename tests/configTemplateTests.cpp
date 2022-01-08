#define CATCH_CONFIG_NO_POSIX_SIGNALS

#include "catch.hpp"

#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include "fibutils/configVariable.hpp"

class Zoo
{
public:
    struct Config
    {
        Fib::Utils::ConfigVariable<const char *> name = Fib::Utils::ConfigVariable<const char *>("Harambe");
        Fib::Utils::ConfigVariable<std::size_t> strength = Fib::Utils::ConfigVariable<std::size_t>(9001);
        Fib::Utils::ConfigVariable<double> charisma = Fib::Utils::ConfigVariable<double>(100.00);
    } config;

    struct Config2
    {
        CONFIG_VARIABLE(const char *, name, "Harambe");
        CONFIG_VARIABLE(std::size_t, strength, 9001);
        CONFIG_VARIABLE(double, charisma, 100.00);
    } config2;
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
