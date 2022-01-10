#include "catch.hpp"

#include "fibstd/uptime.hpp"

#include <cstring>
#include <iostream>

static bool toStringEqual(uint64_t uptimeInMs, const char *expectedOutput)
{
    std::array<char, Fib::Std::Uptime::toStringBufferMinSize> stringBuffer;
    Fib::Std::Uptime::toString(uptimeInMs, stringBuffer.data(), stringBuffer.size());
    // std::cout << stringBuffer.data() << std::endl;
    return (0 == std::strcmp(stringBuffer.data(), expectedOutput));
}

TEST_CASE("uptime")
{
    SECTION("toString0ms")
    {
        REQUIRE(toStringEqual(0, "000:00:00:00.000"));
    }

    SECTION("toString1ms")
    {
        REQUIRE(toStringEqual(1, "000:00:00:00.001"));
    }

    SECTION("toString10ms")
    {
        REQUIRE(toStringEqual(10, "000:00:00:00.010"));
    }

    SECTION("toString100ms")
    {
        REQUIRE(toStringEqual(100, "000:00:00:00.100"));
    }

    SECTION("toString1s")
    {
        REQUIRE(toStringEqual(1000, "000:00:00:01.000"));
    }

    SECTION("toString10s")
    {
        REQUIRE(toStringEqual((10 * 1000), "000:00:00:10.000"));
    }

    SECTION("toString1m")
    {
        REQUIRE(toStringEqual((60 * 1000), "000:00:01:00.000"));
    }

    SECTION("toString10m")
    {
        REQUIRE(toStringEqual((10 * 60 * 1000), "000:00:10:00.000"));
    }

    SECTION("toString1h")
    {
        REQUIRE(toStringEqual((60 * 60 * 1000), "000:01:00:00.000"));
    }

    SECTION("toString10h")
    {
        REQUIRE(toStringEqual((10 * 60 * 60 * 1000), "000:10:00:00.000"));
    }

    SECTION("toString1day")
    {
        REQUIRE(toStringEqual((1 * 24 * 60 * 60 * 1000), "001:00:00:00.000"));
    }

    SECTION("toString10day")
    {
        REQUIRE(toStringEqual((10 * 24 * 60 * 60 * 1000), "010:00:00:00.000"));
    }

    SECTION("toString100day")
    {
        REQUIRE(toStringEqual((100 * 24 * 60 * 60 * 1000ULL), "100:00:00:00.000"));
    }

    SECTION("toStringmax")
    {
        REQUIRE(toStringEqual((1000 * 24 * 60 * 60 * 1000ULL - 1), "999:23:59:59.999"));
    }
}