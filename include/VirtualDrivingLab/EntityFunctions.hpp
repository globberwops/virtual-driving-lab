#pragma once

#include "VirtualDrivingLab/EntityRepository.hpp"
#include "VirtualDrivingLab/Types.hpp"
#include <units/math.h>

#include <cmath>

namespace vdlab
{

template <typename... Components>
[[nodiscard]] inline auto speed(EntityType entity, EntityRepository<Components...> &repo) -> auto
{
    using speed_unit = units::isq::si::speed<units::isq::si::metre_per_second, float>;
    using velocity_t = types::Velocity3<speed_unit>;
    using angle_unit = units::angle<units::radian, float>;
    using angle_t = types::Angle3<angle_unit>;

    const auto [velocity, angle] = repo.template getComponent<velocity_t, angle_t>(entity);

    return magnitude(velocity->get()) * std::cos(angle->get().yaw.number());
}

} // namespace vdlab
