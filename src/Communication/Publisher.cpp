#include "VirtualDrivingLab/Communication/Publisher.hpp"

#include <algorithm>
#include <optional>
#include <string_view>
#include <vector>

namespace vdlab::com
{

auto Publisher::CreateChannel(std::string_view name) noexcept -> std::optional<std::reference_wrapper<ChannelType>>
{
    return m_channels.emplace_back(name);
}

auto Publisher::GetChannel(std::string_view name) noexcept -> std::optional<std::reference_wrapper<ChannelType>>
{
    auto iter = std::find_if(std::begin(m_channels), std::end(m_channels),
                             [name](const auto &channel) { return channel.GetName() == name; });

    if (iter != std::end(m_channels))
    {
        return std::ref(*iter);
    }

    return std::nullopt;
}

} // namespace vdlab::com
