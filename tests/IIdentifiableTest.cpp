#include "VirtualDrivingLab/IIdentifiable.hpp"

#include <doctest/doctest.h>

using vdlab::IIdentifiable;

class Derived : public IIdentifiable
{
};

TEST_SUITE("IIdentifiable")
{
    TEST_CASE("getIdentifier/setIdentifier")
    {
        constexpr auto identifier = 42U;
        auto derived = Derived{};

        SUBCASE("value")
        {
            derived.setIdentifier(identifier);
            REQUIRE_EQ(derived.getIdentifier(), identifier);
        }

        SUBCASE("reference")
        {
            auto &derived_reference = derived;
            derived_reference.setIdentifier(identifier);
            REQUIRE_EQ(derived_reference.getIdentifier(), identifier);
        }

        SUBCASE("const value")
        {
            const auto derived_const = derived;
            REQUIRE_EQ(derived_const.getIdentifier(), 0U);
        }

        SUBCASE("const reference")
        {
            const auto &derived_const = derived;
            REQUIRE_EQ(derived_const.getIdentifier(), 0U);
        }
    }
}
