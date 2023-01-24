#include "VirtualDrivingLab/Communication/Publisher.hpp"

#include "VirtualDrivingLab/Communication/Channel.hpp"

#include <gtest/gtest.h>

using vdlab::com::Publisher;

TEST(PublisherTest, CreateChannels)
{
    const auto channel_name = std::string{::testing::UnitTest::GetInstance()->current_test_suite()->name()} + '.' +
                              ::testing::UnitTest::GetInstance()->current_test_info()->name();

    auto publisher = Publisher{};
    auto channel_one = publisher.CreateChannel(channel_name + "One");
    auto channel_two = publisher.CreateChannel(channel_name + "Two");

    ASSERT_TRUE(channel_one);
    ASSERT_TRUE(channel_two);
}

TEST(PublisherTest, GetChannels)
{
    const auto channel_name = std::string{::testing::UnitTest::GetInstance()->current_test_suite()->name()} + '.' +
                              ::testing::UnitTest::GetInstance()->current_test_info()->name();

    auto publisher = Publisher{};
    publisher.CreateChannel(channel_name + "One");
    publisher.CreateChannel(channel_name + "Two");
    auto channel_one = publisher.GetChannel(channel_name + "One");
    auto channel_two = publisher.GetChannel(channel_name + "Two");

    ASSERT_TRUE(channel_one);
    ASSERT_TRUE(channel_two);
}
