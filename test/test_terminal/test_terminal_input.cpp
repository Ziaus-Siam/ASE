#include <gmock/gmock.h>
#include <Terminal.hpp>
#include <string>

class TestTerminalInput : public ::testing::Test
{
protected:
    Terminal terminal;
    string input;
    void SetUp() override
    {
        GTEST_SKIP() << "Skipping all tests for this fixture";
        input = terminal.get_input();
    }
    void TearDown() override {}
};

TEST_F(TestTerminalInput, get_input_alphabets)
{
    ASSERT_EQ(input, "abcd");
    ASSERT_NE(input, "ABCD");
}

TEST_F(TestTerminalInput, get_input_numbers)
{
    ASSERT_EQ(input, "11527");
}