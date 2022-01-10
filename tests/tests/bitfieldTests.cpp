#include "catch.hpp"

#include "fibstd/bitfield.hpp"

#include <limits>

TEST_CASE("bitfield")
{
    struct SomeReg64
    {
        uint64_t bitfield2 : 2;
        uint64_t bitfield3 : 3;
        uint64_t bitfield4 : 4;
        uint64_t bitfield7 : 7;
        uint64_t bitfield8 : 8;
        uint64_t bitfield16 : 16;
        uint64_t bitfield24 : 24;
    };
    static_assert(sizeof(SomeReg64) == sizeof(uint64_t));

    struct SomeReg32
    {
        uint32_t bitfield1 : 1;
        uint32_t bitfield2 : 2;
        uint32_t bitfield3 : 3;
        uint32_t bitfield4 : 4;
        uint32_t bitfield5 : 5;
        uint32_t bitfield6 : 6;
        uint32_t bitfield7 : 7;
        uint32_t reserved : 4;
    };
    static_assert(sizeof(SomeReg32) == sizeof(uint32_t));

    struct SomeReg16
    {
        uint16_t bitfield1 : 1;
        uint16_t bitfield2 : 2;
        uint16_t bitfield3 : 3;
        uint16_t bitfield4 : 4;
        uint16_t bitfield5 : 5;
        uint16_t reserved : 1;
    };
    static_assert(sizeof(SomeReg16) == sizeof(uint16_t));

    struct SomeReg8
    {
        uint8_t bitfield1 : 1;
        uint8_t bitfield2 : 2;
        uint8_t bitfield3 : 3;
        uint8_t reserved : 2;
    };
    static_assert(sizeof(SomeReg8) == sizeof(uint8_t));

    SECTION("FIBSTD_BITFIELD_WIDTH")
    {
        /* FIBSTD_BITFIELD_WIDTH is resolved during compile-time and can be tested during compilation */
        static_assert(2 == FIBSTD_BITFIELD_WIDTH(SomeReg64, bitfield2));
        static_assert(3 == FIBSTD_BITFIELD_WIDTH(SomeReg64, bitfield3));
        static_assert(4 == FIBSTD_BITFIELD_WIDTH(SomeReg64, bitfield4));
        static_assert(7 == FIBSTD_BITFIELD_WIDTH(SomeReg64, bitfield7));
        static_assert(8 == FIBSTD_BITFIELD_WIDTH(SomeReg64, bitfield8));
        static_assert(16 == FIBSTD_BITFIELD_WIDTH(SomeReg64, bitfield16));
        static_assert(24 == FIBSTD_BITFIELD_WIDTH(SomeReg64, bitfield24));

        static_assert(1 == FIBSTD_BITFIELD_WIDTH(SomeReg32, bitfield1));
        static_assert(2 == FIBSTD_BITFIELD_WIDTH(SomeReg32, bitfield2));
        static_assert(3 == FIBSTD_BITFIELD_WIDTH(SomeReg32, bitfield3));
        static_assert(4 == FIBSTD_BITFIELD_WIDTH(SomeReg32, bitfield4));
        static_assert(5 == FIBSTD_BITFIELD_WIDTH(SomeReg32, bitfield5));
        static_assert(6 == FIBSTD_BITFIELD_WIDTH(SomeReg32, bitfield6));
        static_assert(7 == FIBSTD_BITFIELD_WIDTH(SomeReg32, bitfield7));

        static_assert(1 == FIBSTD_BITFIELD_WIDTH(SomeReg16, bitfield1));
        static_assert(2 == FIBSTD_BITFIELD_WIDTH(SomeReg16, bitfield2));
        static_assert(3 == FIBSTD_BITFIELD_WIDTH(SomeReg16, bitfield3));
        static_assert(4 == FIBSTD_BITFIELD_WIDTH(SomeReg16, bitfield4));
        static_assert(5 == FIBSTD_BITFIELD_WIDTH(SomeReg16, bitfield5));

        static_assert(1 == FIBSTD_BITFIELD_WIDTH(SomeReg8, bitfield1));
        static_assert(2 == FIBSTD_BITFIELD_WIDTH(SomeReg8, bitfield2));
        static_assert(3 == FIBSTD_BITFIELD_WIDTH(SomeReg8, bitfield3));
    }

    SECTION("FIBSTD_BITFIELD_MAX")
    {
        /* FIBSTD_BITFIELD_MAX is resolved during compile-time and can be tested during compilation */
        static_assert(3 == FIBSTD_BITFIELD_MAX(SomeReg64, bitfield2));
        static_assert(7 == FIBSTD_BITFIELD_MAX(SomeReg64, bitfield3));
        static_assert(15 == FIBSTD_BITFIELD_MAX(SomeReg64, bitfield4));
        static_assert(127 == FIBSTD_BITFIELD_MAX(SomeReg64, bitfield7));
        static_assert(255 == FIBSTD_BITFIELD_MAX(SomeReg64, bitfield8));
        static_assert(65535 == FIBSTD_BITFIELD_MAX(SomeReg64, bitfield16));
        static_assert(16777215 == FIBSTD_BITFIELD_MAX(SomeReg64, bitfield24));

        static_assert(1 == FIBSTD_BITFIELD_MAX(SomeReg32, bitfield1));
        static_assert(3 == FIBSTD_BITFIELD_MAX(SomeReg32, bitfield2));
        static_assert(7 == FIBSTD_BITFIELD_MAX(SomeReg32, bitfield3));
        static_assert(15 == FIBSTD_BITFIELD_MAX(SomeReg32, bitfield4));
        static_assert(31 == FIBSTD_BITFIELD_MAX(SomeReg32, bitfield5));
        static_assert(63 == FIBSTD_BITFIELD_MAX(SomeReg32, bitfield6));
        static_assert(127 == FIBSTD_BITFIELD_MAX(SomeReg32, bitfield7));

        static_assert(1 == FIBSTD_BITFIELD_MAX(SomeReg16, bitfield1));
        static_assert(3 == FIBSTD_BITFIELD_MAX(SomeReg16, bitfield2));
        static_assert(7 == FIBSTD_BITFIELD_MAX(SomeReg16, bitfield3));
        static_assert(15 == FIBSTD_BITFIELD_MAX(SomeReg16, bitfield4));
        static_assert(31 == FIBSTD_BITFIELD_MAX(SomeReg16, bitfield5));

        static_assert(1 == FIBSTD_BITFIELD_MAX(SomeReg8, bitfield1));
        static_assert(3 == FIBSTD_BITFIELD_MAX(SomeReg8, bitfield2));
        static_assert(7 == FIBSTD_BITFIELD_MAX(SomeReg8, bitfield3));
    }
}