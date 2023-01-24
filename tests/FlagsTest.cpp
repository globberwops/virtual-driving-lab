#include "VirtualDrivingLab/Flags.hpp"

#include <gtest/gtest.h>

#include <iostream>

namespace vdlab
{

enum class Flags : std::uint8_t
{
    One = 1 << 0,
    Two = 1 << 1,
    Three = 1 << 2
};

namespace compile_time
{

constexpr auto false_flags = Flags{};
static_assert(!test(false_flags, Flags::One));
static_assert(!test(false_flags, Flags::Two));
static_assert(!test(false_flags, Flags::Three));

constexpr auto true_flags = Flags{Flags::One | Flags::Two | Flags::Three};
static_assert(test(true_flags, Flags::One));
static_assert(test(true_flags, Flags::Two));
static_assert(test(true_flags, Flags::Three));

constexpr auto mod_flags = false_flags | Flags::One | Flags::Two;
static_assert(test(mod_flags, Flags::One));
static_assert(test(mod_flags, Flags::Two));
static_assert(!test(mod_flags, Flags::Three));

} // namespace compile_time

TEST(FlagsTest, test)
{
    const auto false_flags = Flags{};

    ASSERT_FALSE(test(false_flags, Flags::One)) << false_flags;
    ASSERT_FALSE(test(false_flags, Flags::Two)) << false_flags;
    ASSERT_FALSE(test(false_flags, Flags::Three)) << false_flags;

    const auto true_flags = Flags{};

    ASSERT_FALSE(test(true_flags, Flags::One)) << true_flags;
    ASSERT_FALSE(test(true_flags, Flags::Two)) << true_flags;
    ASSERT_FALSE(test(true_flags, Flags::Three)) << true_flags;
}

TEST(FlagsTest, OperatorOr)
{
    const auto flags = Flags{Flags::One | Flags::Two};

    ASSERT_TRUE(test(flags, Flags::One)) << flags;
    ASSERT_TRUE(test(flags, Flags::Two)) << flags;
    ASSERT_FALSE(test(flags, Flags::Three)) << flags;
}

TEST(FlagsTest, OperatorOrEquals)
{
    auto flags = Flags{};
    flags |= Flags::One;

    ASSERT_TRUE(test(flags, Flags::One)) << flags;
    ASSERT_FALSE(test(flags, Flags::Two)) << flags;
    ASSERT_FALSE(test(flags, Flags::Three)) << flags;
}

TEST(FlagsTest, OperatorAndEquals)
{
    auto flags = Flags{Flags::One};
    flags &= Flags::One;

    ASSERT_TRUE(test(flags, Flags::One)) << flags;
    ASSERT_FALSE(test(flags, Flags::Two)) << flags;
    ASSERT_FALSE(test(flags, Flags::Three)) << flags;
}

} // namespace vdlab
