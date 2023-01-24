#include <benchmark/benchmark.h>

#include <units/generic/angle.h>
#include <units/isq/si/length.h>
#include <units/isq/si/speed.h>
#include <units/quantity_io.h>

#include "VirtualDrivingLab/EntityRepository.hpp"
#include "VirtualDrivingLab/Types.hpp"

#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-result"

using length_unit = units::isq::si::length<units::isq::si::metre, float>;
using speed_unit = units::isq::si::speed<units::isq::si::metre_per_second, float>;
using angle_unit = units::angle<units::radian, float>;

using name_t = vdlab::types::Name<std::string>;
using position_t = vdlab::types::Point3<length_unit>;
using velocity_t = vdlab::types::Velocity3<speed_unit>;
using angle_t = vdlab::types::Angle3<angle_unit>;

static void BM_GetComponents(benchmark::State &state)
{
    using namespace units::isq::si::literals;
    using namespace units::literals;

    const auto kName{name_t{.name = "Entity"}};
    constexpr auto kPosition{position_t{.x = 1._q_m, .y = 1._q_m, .z = 1._q_m}};
    constexpr auto kVelocity{velocity_t{.x = 1._q_m_per_s, .y = 1._q_m_per_s, .z = 1._q_m_per_s}};
    constexpr auto kOrientation{angle_t{.yaw = 1._q_rad, .pitch = 1._q_rad, .roll = 1._q_rad}};

    auto repo = vdlab::EntityRepository<name_t, position_t, velocity_t, angle_t>{};

    auto entity = repo.addEntity();

    repo.addComponent<name_t, position_t, velocity_t, angle_t>(entity, kName, kPosition, kVelocity, kOrientation);

    for (auto _ : state)
    {
        auto [name, position, velocity, orientation] =
            repo.getComponent<name_t, position_t, velocity_t, angle_t>(entity);
    }
}

// Register the function as a benchmark
BENCHMARK(BM_GetComponents);
