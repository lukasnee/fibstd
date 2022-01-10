#include "catch.hpp"

#include "fibstd/byteswap.hpp"

TEST_CASE("endian")
{
    SECTION("byteswapTwoTimes")
    {
        const uint32_t input = 0x44332211;
        REQUIRE(input == Fib::Std::byteswap(Fib::Std::byteswap(input)));
    }

    SECTION("byteswap8")
    {
        const uint8_t input = 0x12, expectedOutput = 0x12;
        REQUIRE(expectedOutput == Fib::Std::byteswap(input));
    }
    SECTION("byteswap16")
    {
        const uint16_t input = 0x2211, expectedOutput = 0x1122;
        REQUIRE(expectedOutput == Fib::Std::byteswap(input));
    }
    SECTION("byteswap32")
    {
        const uint32_t input = 0x44332211, expectedOutput = 0x11223344;
        REQUIRE(expectedOutput == Fib::Std::byteswap(input));
    }
    SECTION("byteswap64")
    {
        const uint64_t input = 0x8877665544332211, expectedOutput = 0x1122334455667788;
        REQUIRE(expectedOutput == Fib::Std::byteswap(input));
    }

    SECTION("byteswap32In64Frame")
    {
        const uint64_t input = 0x44332211, expectedOutput = 0x1122334400000000;
        REQUIRE(expectedOutput == Fib::Std::byteswap(input));
    }
    SECTION("byteswap16In32Frame")
    {
        const uint32_t u16In32Frame = 0x2211, expected = 0x11220000;
        REQUIRE(expected == Fib::Std::byteswap(u16In32Frame));
    }

    SECTION("byteswap8CompileTime")
    {
        constexpr uint8_t input = 0x12, expectedOutput = 0x12;
        static_assert(expectedOutput == Fib::Std::byteswap(input));
    }
    SECTION("byteswap16CompileTime")
    {
        constexpr uint16_t input = 0x2211, expectedOutput = 0x1122;
        static_assert(expectedOutput == Fib::Std::byteswap(input));
    }
    SECTION("byteswap32CompileTime")
    {
        constexpr uint32_t input = 0x44332211, expectedOutput = 0x11223344;
        static_assert(expectedOutput == Fib::Std::byteswap(input));
    }
    SECTION("byteswap64CompileTime")
    {
        constexpr uint64_t input = 0x8877665544332211, expectedOutput = 0x1122334455667788;
        static_assert(expectedOutput == Fib::Std::byteswap(input));
    }
}