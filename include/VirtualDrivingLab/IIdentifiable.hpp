#pragma once

#include <cstdint>
#include <utility>

namespace vdlab
{

class IIdentifiable
{
    std::uint64_t m_identifier{};

  public:
    [[nodiscard]] constexpr auto getIdentifier() const noexcept
    {
        return m_identifier;
    }

    constexpr auto setIdentifier(std::uint64_t identifier) noexcept
    {
        m_identifier = identifier;
    }
};

} // namespace vdlab
