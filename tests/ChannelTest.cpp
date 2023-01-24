#include "VirtualDrivingLab/Communication/Channel.hpp"

#include <gtest/gtest.h>

namespace vdlab
{

TEST(ChannelTest, CreateReadWrite)
{
    using vdlab::com::Channel;
    using vdlab::com::CreateOnly;

    const auto *channel_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    auto channel = Channel<CreateOnly>{channel_name};
    channel.Write(42);

    ASSERT_EQ(42, channel.Read<int>());
}

TEST(ChannelTest, OpenRead)
{
    using vdlab::com::Channel;
    using vdlab::com::CreateOnly;
    using vdlab::com::OpenOnly;

    const auto *channel_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    auto channel_create = Channel<CreateOnly>{channel_name};
    channel_create.Write(42);
    EXPECT_EQ(42, channel_create.Read<int>());

    auto channel_open = Channel<OpenOnly>{channel_name};
    ASSERT_EQ(42, channel_open.Read<int>());
}

TEST(ChannelTest, Move)
{
    using vdlab::com::Channel;
    using vdlab::com::CreateOnly;

    const auto *channel_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    auto moved_from = Channel<CreateOnly>{channel_name};
    moved_from.Write(42);

    auto moved_to = Channel{std::move(moved_from)};

    ASSERT_EQ(42, moved_to.Read<int>());
    ASSERT_TRUE(moved_from.GetName().empty());
}

} // namespace vdlab
