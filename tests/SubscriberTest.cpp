#include "VirtualDrivingLab/Communication/Subscriber.hpp"

#include "VirtualDrivingLab/Communication/Channel.hpp"
#include "VirtualDrivingLab/Communication/Publisher.hpp"

#include <gtest/gtest.h>

using vdlab::com::Publisher;
using vdlab::com::Subscriber;

TEST(SubscriberTest, OpenChannels)
{
    const auto channel_name = std::string{::testing::UnitTest::GetInstance()->current_test_suite()->name()} + '.' +
                              ::testing::UnitTest::GetInstance()->current_test_info()->name();

    auto publisher = Publisher{};
    auto pub_channel_one = publisher.CreateChannel(channel_name + "One");
    auto pub_channel_two = publisher.CreateChannel(channel_name + "Two");

    ASSERT_TRUE(pub_channel_one);
    ASSERT_TRUE(pub_channel_two);

    auto subscriber = Subscriber{};
    auto sub_channel_one = subscriber.OpenChannel(channel_name + "One");
    auto sub_channel_two = subscriber.OpenChannel(channel_name + "Two");

    ASSERT_TRUE(sub_channel_one);
    ASSERT_TRUE(sub_channel_two);
}

TEST(SubscriberTest, GetChannels)
{
    const auto channel_name = std::string{::testing::UnitTest::GetInstance()->current_test_suite()->name()} + '.' +
                              ::testing::UnitTest::GetInstance()->current_test_info()->name();

    auto publisher = Publisher{};
    auto pub_channel_one = publisher.CreateChannel(channel_name + "One");
    auto pub_channel_two = publisher.CreateChannel(channel_name + "Two");

    ASSERT_TRUE(pub_channel_one);
    ASSERT_TRUE(pub_channel_two);

    auto subscriber = Subscriber{};
    subscriber.OpenChannel(channel_name + "One");
    subscriber.OpenChannel(channel_name + "Two");
    auto sub_channel_one = subscriber.GetChannel(channel_name + "One");
    auto sub_channel_two = subscriber.GetChannel(channel_name + "Two");

    ASSERT_TRUE(sub_channel_one);
    ASSERT_TRUE(sub_channel_two);
}
