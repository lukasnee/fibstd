#include "catch.hpp"

#include "fibstd/cast.hpp"
TEST_CASE("enumValue")
{

    enum class SomeState : std::uint8_t
    {
        undefined = 0,
        off,
        standby,
        busy,
        _size
    };

    constexpr std::uint8_t someStateValueBusyExpected = 3;

    SECTION("toUnderlying")
    {
        REQUIRE(Fib::Std::Cast::toUnderlying(SomeState::busy) == someStateValueBusyExpected);
        static_assert(Fib::Std::Cast::toUnderlying(SomeState::busy) == someStateValueBusyExpected);
    }

    SECTION("toEnum")
    {
        static_assert(Fib::Std::Cast::toEnum<SomeState>(someStateValueBusyExpected) == SomeState::busy);
        REQUIRE(Fib::Std::Cast::toEnum<SomeState>(someStateValueBusyExpected) == SomeState::busy);
    }
}