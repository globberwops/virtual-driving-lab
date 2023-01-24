#pragma once

namespace vdlab
{

template <typename Derived>
struct IStepable
{
    constexpr auto preStep() noexcept
    {
        auto &derived = static_cast<Derived &>(*this);
        return derived.doPreStep();
    }

    constexpr auto step() noexcept
    {
        auto &derived = static_cast<Derived &>(*this);
        return derived.doStep();
    }

    constexpr auto postStep() noexcept
    {
        auto &derived = static_cast<Derived &>(*this);
        return derived.doPostStep();
    }
};

} // namespace vdlab
