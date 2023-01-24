#include <gtest/gtest.h>

#include <units/generic/angle.h>
#include <units/isq/si/acceleration.h>
#include <units/isq/si/angular_velocity.h>
#include <units/isq/si/length.h>
#include <units/isq/si/speed.h>
#include <units/quantity_io.h>

#include <iostream>
#include <sstream>

#include "VirtualDrivingLab/Types.hpp"

TEST(TypesTest, NameComparison)
{
    using name_t = vdlab::types::Name<std::string>;

    const auto name1{name_t{.name{"Same"}}};
    const auto name2{name_t{.name{"Same"}}};
    const auto name3{name_t{.name{"Other"}}};

    ASSERT_TRUE(name1 == name2);
    ASSERT_TRUE(name2 != name3);
}

TEST(TypesTest, NameStream)
{
    using name_t = vdlab::types::Name<std::string>;

    auto name{name_t{.name{"Stream"}}};
    auto stream{std::stringstream{}};
    stream << name;

    ASSERT_STREQ(stream.str().c_str(), name.name.c_str());
}

TEST(TypesTest, Point3Comparison)
{
    using length_unit = units::isq::si::length<units::isq::si::metre, float>;
    using point_t = vdlab::types::Point3<length_unit>;
    using namespace units::isq::si::references;

    constexpr auto point1{point_t{.x{1.F * m}, .y{1.F * m}, .z{1.F * m}}};
    constexpr auto point2{point_t{.x{1.F * m}, .y{1.F * m}, .z{1.F * m}}};
    constexpr auto point3{point_t{.x{2.F * m}, .y{2.F * m}, .z{2.F * m}}};

    static_assert(point1 == point2);
    static_assert(point2 != point3);
}

TEST(TypesTest, Point3Stream)
{
    using length_unit = units::isq::si::length<units::isq::si::metre, float>;
    using point_t = vdlab::types::Point3<length_unit>;
    using namespace units::isq::si::references;

    constexpr auto point{point_t{.x{1.F * m}, .y{1.F * m}, .z{1.F * m}}};
    auto stream{std::stringstream{}};
    stream << point;

    ASSERT_STREQ(stream.str().c_str(), "1 m, 1 m, 1 m");
}

TEST(TypesTest, Point3Arithmetic)
{
    using length_unit = units::isq::si::length<units::isq::si::metre, float>;
    using point_t = vdlab::types::Point3<length_unit>;
    using namespace units::isq::si::references;

    constexpr auto point1{point_t{.x{1.F * m}, .y{1.F * m}, .z{1.F * m}}};
    constexpr auto point2{point_t{.x{1.F * m}, .y{1.F * m}, .z{1.F * m}}};
    constexpr auto point3{point_t{.x{2.F * m}, .y{2.F * m}, .z{2.F * m}}};

    static_assert(point1 + point2 == point3);
    static_assert(point3 - point2 == point1);
    static_assert(point1 * 2.F == point3);
    static_assert(point3 / 2.F == point1);
}

TEST(TypesTest, Velocity3Comparison)
{
    using speed_unit = units::isq::si::speed<units::isq::si::metre_per_second, float>;
    using velocity_t = vdlab::types::Velocity3<speed_unit>;
    using namespace units::isq::si::references;

    constexpr auto velocity1{velocity_t{.x{1.F * (m / s)}, .y{1.F * (m / s)}, .z{1.F * (m / s)}}};
    constexpr auto velocity2{velocity_t{.x{1.F * (m / s)}, .y{1.F * (m / s)}, .z{1.F * (m / s)}}};
    constexpr auto velocity3{velocity_t{.x{2.F * (m / s)}, .y{2.F * (m / s)}, .z{2.F * (m / s)}}};

    static_assert(velocity1 == velocity2);
    static_assert(velocity2 != velocity3);
}

TEST(TypesTest, Velocity3Stream)
{
    using speed_unit = units::isq::si::speed<units::isq::si::metre_per_second, float>;
    using velocity_t = vdlab::types::Velocity3<speed_unit>;
    using namespace units::isq::si::references;

    constexpr auto velocity{velocity_t{.x{1.F * (m / s)}, .y{1.F * (m / s)}, .z{1.F * (m / s)}}};
    auto stream{std::stringstream{}};
    stream << velocity;

    ASSERT_STREQ(stream.str().c_str(), "1 m/s, 1 m/s, 1 m/s");
}

TEST(TypesTest, Velocity3Arithmetic)
{
    using speed_unit = units::isq::si::speed<units::isq::si::metre_per_second, float>;
    using velocity_t = vdlab::types::Velocity3<speed_unit>;
    using namespace units::isq::si::references;

    constexpr auto velocity1{velocity_t{.x{1.F * (m / s)}, .y{1.F * (m / s)}, .z{1.F * (m / s)}}};
    constexpr auto velocity2{velocity_t{.x{1.F * (m / s)}, .y{1.F * (m / s)}, .z{1.F * (m / s)}}};
    constexpr auto velocity3{velocity_t{.x{2.F * (m / s)}, .y{2.F * (m / s)}, .z{2.F * (m / s)}}};
    constexpr auto velocity4{velocity_t{.x{2.F * (m / s)}, .y{0.F * (m / s)}, .z{0.F * (m / s)}}};
    constexpr auto velocity5{velocity_t{.x{-2.F * (m / s)}, .y{0.F * (m / s)}, .z{0.F * (m / s)}}};

    static_assert(velocity1 + velocity2 == velocity3);
    static_assert(velocity3 - velocity2 == velocity1);
    static_assert(velocity1 * 2.F == velocity3);
    static_assert(velocity3 / 2.F == velocity1);

    ASSERT_TRUE(magnitude(velocity4) == 2.F * (m / s));

    static_assert(velocity1 * velocity1 == 3.F * ((m * m) / (s * s)));
    static_assert(velocity3 * velocity3 == 12.F * ((m * m) / (s * s)));

    ASSERT_TRUE(abs(velocity5) == velocity4);
}

TEST(TypesTest, Acceleration3Comparison)
{
    using acceleration_unit = units::isq::si::acceleration<units::isq::si::metre_per_second_sq, float>;
    using acceleration_t = vdlab::types::Acceleration3<acceleration_unit>;
    using namespace units::isq::si::references;

    constexpr auto acceleration1{
        acceleration_t{.x{1.F * (m / (s * s))}, .y{1.F * (m / (s * s))}, .z{1.F * (m / (s * s))}}};
    constexpr auto acceleration2{
        acceleration_t{.x{1.F * (m / (s * s))}, .y{1.F * (m / (s * s))}, .z{1.F * (m / (s * s))}}};
    constexpr auto acceleration3{
        acceleration_t{.x{2.F * (m / (s * s))}, .y{2.F * (m / (s * s))}, .z{2.F * (m / (s * s))}}};

    static_assert(acceleration1 == acceleration2);
    static_assert(acceleration2 != acceleration3);
}

TEST(TypesTest, Acceleration3Stream)
{
    using acceleration_unit = units::isq::si::acceleration<units::isq::si::metre_per_second_sq, float>;
    using acceleration_t = vdlab::types::Acceleration3<acceleration_unit>;
    using namespace units::isq::si::references;

    constexpr auto acceleration{
        acceleration_t{.x{1.F * (m / (s * s))}, .y{1.F * (m / (s * s))}, .z{1.F * (m / (s * s))}}};
    auto stream{std::stringstream{}};
    stream << acceleration;

    ASSERT_STREQ(stream.str().c_str(), "1 m/s², 1 m/s², 1 m/s²");
}

TEST(TypesTest, Acceleration3Arithmetic)
{
    using acceleration_unit = units::isq::si::acceleration<units::isq::si::metre_per_second_sq, float>;
    using acceleration_t = vdlab::types::Acceleration3<acceleration_unit>;
    using namespace units::isq::si::references;

    constexpr auto acceleration1{
        acceleration_t{.x{1.F * (m / (s * s))}, .y{1.F * (m / (s * s))}, .z{1.F * (m / (s * s))}}};
    constexpr auto acceleration2{
        acceleration_t{.x{1.F * (m / (s * s))}, .y{1.F * (m / (s * s))}, .z{1.F * (m / (s * s))}}};
    constexpr auto acceleration3{
        acceleration_t{.x{2.F * (m / (s * s))}, .y{2.F * (m / (s * s))}, .z{2.F * (m / (s * s))}}};
    constexpr auto acceleration4{
        acceleration_t{.x{2.F * (m / (s * s))}, .y{0.F * (m / (s * s))}, .z{0.F * (m / (s * s))}}};

    static_assert(acceleration1 + acceleration2 == acceleration3);
    static_assert(acceleration3 - acceleration2 == acceleration1);
    static_assert(acceleration1 * 2.F == acceleration3);
    static_assert(acceleration3 / 2.F == acceleration1);

    ASSERT_TRUE(magnitude(acceleration4) == 2.F * (m / (s * s)));
}

TEST(TypesTest, Angle3Comparison)
{
    using angle_unit = units::angle<units::radian, float>;
    using angle_t = vdlab::types::Angle3<angle_unit>;
    using namespace units::references;

    constexpr auto angle1{angle_t{.yaw{1.F * rad}, .pitch{1.F * rad}, .roll{1.F * rad}}};
    constexpr auto angle2{angle_t{.yaw{1.F * rad}, .pitch{1.F * rad}, .roll{1.F * rad}}};
    constexpr auto angle3{angle_t{.yaw{2.F * rad}, .pitch{2.F * rad}, .roll{2.F * rad}}};

    static_assert(angle1 == angle2);
    static_assert(angle2 != angle3);
}

TEST(TypesTest, Angle3Stream)
{
    using angle_unit = units::angle<units::radian, float>;
    using angle_t = vdlab::types::Angle3<angle_unit>;
    using namespace units::references;

    constexpr auto angle{angle_t{.yaw{1.F * rad}, .pitch{1.F * rad}, .roll{1.F * rad}}};
    auto stream{std::stringstream{}};
    stream << angle;

    ASSERT_STREQ(stream.str().c_str(), "1 rad, 1 rad, 1 rad");
}

TEST(TypesTest, Angle3Arithmetic)
{
    using angle_unit = units::angle<units::radian, float>;
    using angle_t = vdlab::types::Angle3<angle_unit>;
    using namespace units::references;

    constexpr auto angle1{angle_t{.yaw{1.F * rad}, .pitch{1.F * rad}, .roll{1.F * rad}}};
    constexpr auto angle2{angle_t{.yaw{1.F * rad}, .pitch{1.F * rad}, .roll{1.F * rad}}};
    constexpr auto angle3{angle_t{.yaw{2.F * rad}, .pitch{2.F * rad}, .roll{2.F * rad}}};

    static_assert(angle1 + angle2 == angle3);
    static_assert(angle3 - angle2 == angle1);
    static_assert(angle1 * 2.F == angle3);
    static_assert(angle3 / 2.F == angle1);
}

TEST(TypesTest, AngularVelocity3Comparison)
{
    using angular_velocity_unit = units::isq::si::angular_velocity<units::isq::si::radian_per_second, float>;
    using angular_velocity_t = vdlab::types::AngularVelocity3<angular_velocity_unit>;
    using namespace units::references;
    using namespace units::isq::si::references;

    constexpr auto angular_velocity1{
        angular_velocity_t{.yaw{1.F * (rad / s)}, .pitch{1.F * (rad / s)}, .roll{1.F * (rad / s)}}};
    constexpr auto angular_velocity2{
        angular_velocity_t{.yaw{1.F * (rad / s)}, .pitch{1.F * (rad / s)}, .roll{1.F * (rad / s)}}};
    constexpr auto angular_velocity3{
        angular_velocity_t{.yaw{2.F * (rad / s)}, .pitch{2.F * (rad / s)}, .roll{2.F * (rad / s)}}};

    static_assert(angular_velocity1 == angular_velocity2);
    static_assert(angular_velocity2 != angular_velocity3);
}

TEST(TypesTest, AngularVelocity3Stream)
{
    using angular_velocity_unit = units::isq::si::angular_velocity<units::isq::si::radian_per_second, float>;
    using angular_velocity_t = vdlab::types::AngularVelocity3<angular_velocity_unit>;
    using namespace units::references;
    using namespace units::isq::si::references;

    constexpr auto angular_velocity{
        angular_velocity_t{.yaw{1.F * (rad / s)}, .pitch{1.F * (rad / s)}, .roll{1.F * (rad / s)}}};
    auto stream{std::stringstream{}};
    stream << angular_velocity;

    ASSERT_STREQ(stream.str().c_str(), "1 ω, 1 ω, 1 ω");
}

TEST(TypesTest, AngularVelocity3Arithmetic)
{
    using angular_velocity_unit = units::isq::si::angular_velocity<units::isq::si::radian_per_second, float>;
    using angular_velocity_t = vdlab::types::AngularVelocity3<angular_velocity_unit>;
    using namespace units::references;
    using namespace units::isq::si::references;

    constexpr auto angular_velocity1{
        angular_velocity_t{.yaw{1.F * (rad / s)}, .pitch{1.F * (rad / s)}, .roll{1.F * (rad / s)}}};
    constexpr auto angular_velocity2{
        angular_velocity_t{.yaw{1.F * (rad / s)}, .pitch{1.F * (rad / s)}, .roll{1.F * (rad / s)}}};
    constexpr auto angular_velocity3{
        angular_velocity_t{.yaw{2.F * (rad / s)}, .pitch{2.F * (rad / s)}, .roll{2.F * (rad / s)}}};

    static_assert(angular_velocity1 + angular_velocity2 == angular_velocity3);
    static_assert(angular_velocity3 - angular_velocity2 == angular_velocity1);
    static_assert(angular_velocity1 * 2.F == angular_velocity3);
    static_assert(angular_velocity3 / 2.F == angular_velocity1);
}
