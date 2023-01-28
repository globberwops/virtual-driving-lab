#include "VirtualDrivingLab/Flags.hpp"

#include <doctest/doctest.h>

#include <gtest/gtest.h>

#include <iostream>

#define STATIC_REQUIRE(x)                                                                                              \
    static_assert(x);                                                                                                  \
    REQUIRE(x)

namespace vdlab
{

enum class Flags : std::uint8_t
{
    One = 1 << 0,
    Two = 1 << 1,
    Three = 1 << 2
};

} // namespace vdlab

using vdlab::Flags;
using vdlab::test;

TEST_SUITE("FlagsTest")
{
    TEST_CASE("Flags: test, operator|")
    {
        constexpr auto false_flags = Flags{};
        STATIC_REQUIRE(!test(false_flags, Flags::One));
        STATIC_REQUIRE(!test(false_flags, Flags::Two));
        STATIC_REQUIRE(!test(false_flags, Flags::Three));

        constexpr auto true_flags = Flags{Flags::One | Flags::Two | Flags::Three};
        STATIC_REQUIRE(test(true_flags, Flags::One));
        STATIC_REQUIRE(test(true_flags, Flags::Two));
        STATIC_REQUIRE(test(true_flags, Flags::Three));

        constexpr auto mod_flags = false_flags | Flags::One | Flags::Two;
        STATIC_REQUIRE(test(mod_flags, Flags::One));
        STATIC_REQUIRE(test(mod_flags, Flags::Two));
        STATIC_REQUIRE(!test(mod_flags, Flags::Three));
    }

    TEST_CASE("Flags: operator|=")
    {
        auto flags = Flags{};
        flags |= Flags::One;

        REQUIRE_UNARY(test(flags, Flags::One));
        REQUIRE_UNARY_FALSE(test(flags, Flags::Two));
        REQUIRE_UNARY_FALSE(test(flags, Flags::Three));
    }

    TEST_CASE("Flags: operator&=")
    {
        auto flags = Flags{Flags::One};
        flags &= Flags::One;

        REQUIRE_UNARY(test(flags, Flags::One));
        REQUIRE_UNARY_FALSE(test(flags, Flags::Two));
        REQUIRE_UNARY_FALSE(test(flags, Flags::Three));
    }
}
