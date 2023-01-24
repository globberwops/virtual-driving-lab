#include "VirtualDrivingLab/IStepable.hpp"

#include <doctest/doctest.h>

using vdlab::IStepable;

struct Derived : public IStepable<Derived>
{
    constexpr auto doPreStep() noexcept
    {
        return true;
    }

    constexpr auto doStep() noexcept
    {
        return true;
    }

    constexpr auto doPostStep() noexcept
    {
        return true;
    }
};

TEST_CASE("IStepable")
{
    SUBCASE("getIdentifier/setIdentifier")
    {
        auto derived = Derived{};

        REQUIRE_UNARY(derived.preStep());
        REQUIRE_UNARY(derived.step());
        REQUIRE_UNARY(derived.postStep());
    }
}
