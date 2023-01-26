#include <gmock/gmock.h>
#include <RTC.hpp>
#include <ctime>

class TestRTC : public ::testing::Test
{
protected:
    RTC timer;
    void SetUp() override
    {
    }
    void TearDown() override {}
};

TEST_F(TestRTC, getting_time)
{
    ASSERT_EQ(timer.get_time(), time(0));
}