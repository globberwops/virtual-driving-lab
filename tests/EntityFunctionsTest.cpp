#include "VirtualDrivingLab/EntityFunctions.hpp"

#include "VirtualDrivingLab/Types.hpp"

#include <gtest/gtest.h>

#include <cmath>

TEST(EntityFunctionsTest, GetSpeed)
{
    using speed_unit = units::isq::si::speed<units::isq::si::metre_per_second, float>;
    using velocity_t = vdlab::types::Velocity3<speed_unit>;
    using angle_unit = units::angle<units::radian, float>;
    using angle_t = vdlab::types::Angle3<angle_unit>;
    using namespace units::isq::si::references;
    using namespace units::references;

    constexpr auto velocity{velocity_t{.x{}, .y{10.F * (m / s)}, .z{}}};
    constexpr auto angle{angle_t{.yaw{}, .pitch{}, .roll{}}};

    auto repo{vdlab::EntityRepository<velocity_t, angle_t>{}};
    auto entity = repo.addEntity();
    EXPECT_EQ(entity, 0U);
    repo.addComponent(entity, velocity, angle);

    const auto kSpeed = vdlab::speed(entity, repo);

    ASSERT_TRUE(false) << kSpeed;
}
