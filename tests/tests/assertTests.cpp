#include "catch.hpp"

#include "fibstd/assert.hpp"

#include <cstring>

TEST_CASE("assert")
{
    SECTION("assert success")
    {
        FIBSTD_ASSERT(true);
        INFO(Fib::Std::assertInfo.fileline);
        REQUIRE(Fib::Std::assertInfo.fileline[0] == '\0');
    }
    
    SECTION("assert fail")
    {
        FIBSTD_ASSERT(false);
        INFO(Fib::Std::assertInfo.fileline);
        REQUIRE(nullptr != std::strstr(Fib::Std::assertInfo.fileline, "assertTests.cpp:18"));
    }
}