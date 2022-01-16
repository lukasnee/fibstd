#include "catch.hpp"

#include "fibstd/map.hpp"

#include <string_view>

TEST_CASE("constexprMapOfEnumToInt")
{
    enum class Color
    {
        // clang-format off
        black, blue, cyan, green, magenta, red, white, yellow
        // clang-format on
    };

    static constexpr std::array<std::pair<Color, int>, 8> color_values{{{Color::black, 7},
                                                                        {Color::blue, 3},
                                                                        {Color::cyan, 5},
                                                                        {Color::green, 2},
                                                                        {Color::magenta, 6},
                                                                        {Color::red, 1},
                                                                        {Color::white, 8},
                                                                        {Color::yellow, 4}}};
    constexpr auto map = Fib::Std::Map<Color, int, color_values.size()>{{color_values}};

    SECTION("atFound")
    {
        constexpr auto color = map.at(Color::magenta);
        static_assert(color == 6);
        REQUIRE(color == 6);
    }
}

TEST_CASE("constexprMapOfStringViewToInt")
{
    using namespace std::literals::string_view_literals;
    static constexpr std::array<std::pair<std::string_view, int>, 8> color_values{{{"black"sv, 7},
                                                                                   {"blue"sv, 3},
                                                                                   {"cyan"sv, 5},
                                                                                   {"green"sv, 2},
                                                                                   {"magenta"sv, 6},
                                                                                   {"red"sv, 1},
                                                                                   {"white"sv, 8},
                                                                                   {"yellow"sv, 4}}};
    constexpr auto map = Fib::Std::Map<std::string_view, int, color_values.size()>{{color_values}};

    SECTION("atFound")
    {
        constexpr auto color = map.at("yellow"sv);
        static_assert(color == 4);
        REQUIRE(color == 4);
    }

    SECTION("atNotFound")
    {
        constexpr auto color = map.at("yelow"sv);
        static_assert(color != 4);
        REQUIRE(color != 4);
    }
}