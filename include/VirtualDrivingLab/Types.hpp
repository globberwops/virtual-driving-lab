#pragma once

#include "VirtualDrivingLab/Concepts.hpp"
#include <units/generic/angle.h>
#include <units/isq/dimensions/length.h>
#include <units/isq/si/acceleration.h>
#include <units/isq/si/angular_velocity.h>
#include <units/isq/si/length.h>
#include <units/isq/si/speed.h>
#include <units/math.h>
#include <units/quantity_io.h>

#include <cstdint>
#include <ostream>

namespace vdlab::types
{

using units::Angle;
using units::isq::Acceleration;
using units::isq::AngularVelocity;
using units::isq::Length;
using units::isq::Speed;

template <typename T>
struct Name
{
    T name{};

    // NOLINTNEXTLINE(modernize-use-trailing-return-type)
    friend auto operator<=>(const Name &, const Name &) = default;

    friend auto operator<<(std::ostream &os, const Name &value) -> std::ostream &
    {
        os << value.name;
        return os;
    }
};

template <Length T>
struct Point3
{
    T x{};
    T y{};
    T z{};

    // NOTE(globberwops): Add floating point comparison
    // NOLINTNEXTLINE(modernize-use-trailing-return-type)
    friend auto operator<=>(const Point3 &, const Point3 &) = default;

    friend auto operator<<(std::ostream &os, const Point3 &value) -> std::ostream &
    {
        os << value.x << ", " << value.y << ", " << value.z;
        return os;
    }

    [[nodiscard]] friend constexpr auto operator+(const Point3 &lhs, const Point3 &rhs) -> Point3<T>
    {
        return {.x{lhs.x + rhs.x}, .y{lhs.y + rhs.y}, .z{lhs.z + rhs.z}};
    }

    [[nodiscard]] friend constexpr auto operator-(const Point3 &lhs, const Point3 &rhs) -> Point3<T>
    {
        return {.x{lhs.x - rhs.x}, .y{lhs.y - rhs.y}, .z{lhs.z - rhs.z}};
    }

    [[nodiscard]] friend constexpr auto operator*(const Point3 &lhs, Scalar auto rhs) -> Point3<T>
    {
        return {.x{lhs.x * rhs}, .y{lhs.y * rhs}, .z{lhs.z * rhs}};
    }

    [[nodiscard]] friend constexpr auto operator/(const Point3 &lhs, Scalar auto rhs) -> Point3<T>
    {
        return {.x{lhs.x / rhs}, .y{lhs.y / rhs}, .z{lhs.z / rhs}};
    }
};

template <Speed T>
struct Velocity3
{
    T x{};
    T y{};
    T z{};

    // NOTE(globberwops): Add floating point comparison
    // NOLINTNEXTLINE(modernize-use-trailing-return-type)
    friend auto operator<=>(const Velocity3 &, const Velocity3 &) = default;

    friend auto operator<<(std::ostream &os, const Velocity3 &value) -> std::ostream &
    {
        os << value.x << ", " << value.y << ", " << value.z;
        return os;
    }

    [[nodiscard]] friend constexpr auto operator+(const Velocity3 &lhs, const Velocity3 &rhs) -> Velocity3<T>
    {
        return {.x{lhs.x + rhs.x}, .y{lhs.y + rhs.y}, .z{lhs.z + rhs.z}};
    }

    [[nodiscard]] friend constexpr auto operator-(const Velocity3 &lhs, const Velocity3 &rhs) -> Velocity3<T>
    {
        return {.x{lhs.x - rhs.x}, .y{lhs.y - rhs.y}, .z{lhs.z - rhs.z}};
    }

    [[nodiscard]] friend constexpr auto operator*(const Velocity3 &lhs, Scalar auto rhs) -> Velocity3<T>
    {
        return {.x{lhs.x * rhs}, .y{lhs.y * rhs}, .z{lhs.z * rhs}};
    }

    ///
    /// \brief The dot product of two vectors
    /// \param[in] lhs
    /// \param[in] rhs
    /// \return The dot product
    ///
    [[nodiscard]] friend constexpr auto operator*(const Velocity3 &lhs, const Velocity3 &rhs) -> auto
    {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }

    [[nodiscard]] friend constexpr auto operator/(const Velocity3 &lhs, Scalar auto rhs) -> Velocity3<T>
    {
        return {.x{lhs.x / rhs}, .y{lhs.y / rhs}, .z{lhs.z / rhs}};
    }

    [[nodiscard]] friend inline auto magnitude(const Velocity3 &value) -> T
    {
        using units::pow;
        using units::sqrt;
        return sqrt(pow<2>(value.x) + pow<2>(value.y) + pow<2>(value.z));
    }

    [[nodiscard]] friend inline auto abs(const Velocity3 &value) -> Velocity3<T>
    {
        using units::abs;
        return {abs(value.x), abs(value.y), abs(value.z)};
    }
};

template <Acceleration T>
struct Acceleration3
{
    T x{};
    T y{};
    T z{};

    // NOTE(globberwops): Add floating point comparison
    // NOLINTNEXTLINE(modernize-use-trailing-return-type)
    friend auto operator<=>(const Acceleration3 &, const Acceleration3 &) = default;

    friend auto operator<<(std::ostream &os, const Acceleration3 &value) -> std::ostream &
    {
        os << value.x << ", " << value.y << ", " << value.z;
        return os;
    }

    [[nodiscard]] friend constexpr auto operator+(const Acceleration3 &lhs, const Acceleration3 &rhs)
        -> Acceleration3<T>
    {
        return {.x{lhs.x + rhs.x}, .y{lhs.y + rhs.y}, .z{lhs.z + rhs.z}};
    }

    [[nodiscard]] friend constexpr auto operator-(const Acceleration3 &lhs, const Acceleration3 &rhs)
        -> Acceleration3<T>
    {
        return {.x{lhs.x - rhs.x}, .y{lhs.y - rhs.y}, .z{lhs.z - rhs.z}};
    }

    [[nodiscard]] friend constexpr auto operator*(const Acceleration3 &lhs, Scalar auto rhs) -> Acceleration3<T>
    {
        return {.x{lhs.x * rhs}, .y{lhs.y * rhs}, .z{lhs.z * rhs}};
    }

    [[nodiscard]] friend constexpr auto operator/(const Acceleration3 &lhs, Scalar auto rhs) -> Acceleration3<T>
    {
        return {.x{lhs.x / rhs}, .y{lhs.y / rhs}, .z{lhs.z / rhs}};
    }

    [[nodiscard]] friend inline auto magnitude(const Acceleration3 &value) -> T
    {
        using units::pow;
        using units::sqrt;
        return sqrt(pow<2>(value.x) + pow<2>(value.y) + pow<2>(value.z));
    }
};

// NOTE(globberwops): see https://en.wikipedia.org/wiki/Euler_angles#Tait%E2%80%93Bryan_angles
template <Angle T>
struct Angle3
{
    T yaw{};
    T pitch{};
    T roll{};

    // NOTE(globberwops): Add floating point comparison
    // NOLINTNEXTLINE(modernize-use-trailing-return-type)
    friend auto operator<=>(const Angle3 &, const Angle3 &) = default;

    friend auto operator<<(std::ostream &os, const Angle3 &value) -> std::ostream &
    {
        os << value.yaw << ", " << value.pitch << ", " << value.roll;
        return os;
    }

    [[nodiscard]] friend constexpr auto operator+(const Angle3 &lhs, const Angle3 &rhs) -> Angle3<T>
    {
        return {.yaw{lhs.yaw + rhs.yaw}, .pitch{lhs.pitch + rhs.pitch}, .roll{lhs.roll + rhs.roll}};
    }

    [[nodiscard]] friend constexpr auto operator-(const Angle3 &lhs, const Angle3 &rhs) -> Angle3<T>
    {
        return {.yaw{lhs.yaw - rhs.yaw}, .pitch{lhs.pitch - rhs.pitch}, .roll{lhs.roll - rhs.roll}};
    }

    [[nodiscard]] friend constexpr auto operator*(const Angle3 &lhs, Scalar auto rhs) -> Angle3<T>
    {
        return {.yaw{lhs.yaw * rhs}, .pitch{lhs.pitch * rhs}, .roll{lhs.roll * rhs}};
    }

    [[nodiscard]] friend constexpr auto operator/(const Angle3 &lhs, Scalar auto rhs) -> Angle3<T>
    {
        return {.yaw{lhs.yaw / rhs}, .pitch{lhs.pitch / rhs}, .roll{lhs.roll / rhs}};
    }
};

template <AngularVelocity T>
struct AngularVelocity3
{
    T yaw{};
    T pitch{};
    T roll{};

    // NOTE(globberwops): Add floating point comparison
    // NOLINTNEXTLINE(modernize-use-trailing-return-type)
    friend auto operator<=>(const AngularVelocity3 &, const AngularVelocity3 &) = default;

    friend auto operator<<(std::ostream &os, const AngularVelocity3 &value) -> std::ostream &
    {
        os << value.yaw << ", " << value.pitch << ", " << value.roll;
        return os;
    }

    [[nodiscard]] friend constexpr auto operator+(const AngularVelocity3 &lhs, const AngularVelocity3 &rhs)
        -> AngularVelocity3<T>
    {
        return {.yaw{lhs.yaw + rhs.yaw}, .pitch{lhs.pitch + rhs.pitch}, .roll{lhs.roll + rhs.roll}};
    }

    [[nodiscard]] friend constexpr auto operator-(const AngularVelocity3 &lhs, const AngularVelocity3 &rhs)
        -> AngularVelocity3<T>
    {
        return {.yaw{lhs.yaw - rhs.yaw}, .pitch{lhs.pitch - rhs.pitch}, .roll{lhs.roll - rhs.roll}};
    }

    [[nodiscard]] friend constexpr auto operator*(const AngularVelocity3 &lhs, Scalar auto rhs) -> AngularVelocity3<T>
    {
        return {.yaw{lhs.yaw * rhs}, .pitch{lhs.pitch * rhs}, .roll{lhs.roll * rhs}};
    }

    [[nodiscard]] friend constexpr auto operator/(const AngularVelocity3 &lhs, Scalar auto rhs) -> AngularVelocity3<T>
    {
        return {.yaw{lhs.yaw / rhs}, .pitch{lhs.pitch / rhs}, .roll{lhs.roll / rhs}};
    }
};

// TEMP
template <typename T, typename U>
[[nodiscard]] constexpr auto operator*(const Velocity3<T> &lhs, const Angle3<U> &rhs) -> auto
{
    return lhs.x * rhs.yaw + lhs.y * rhs.pitch + lhs.z * rhs.roll;
}

//

} // namespace vdlab::types
