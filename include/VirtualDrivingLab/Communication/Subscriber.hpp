#pragma once

#include "VirtualDrivingLab/Communication/Channel.hpp"

#include <optional>
#include <string_view>
#include <vector>

namespace vdlab::com
{

class Subscriber
{
    using ChannelType = Channel<OpenOnly>;

  public:
    ~Subscriber() noexcept = default;

    auto OpenChannel(std::string_view name) noexcept -> std::optional<std::reference_wrapper<ChannelType>>;
    auto GetChannel(std::string_view name) noexcept -> std::optional<std::reference_wrapper<ChannelType>>;

  private:
    std::vector<ChannelType> m_channels;
};

} // namespace vdlab::com
