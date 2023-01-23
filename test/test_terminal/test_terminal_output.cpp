#include <gmock/gmock.h>
#include <Terminal.hpp>
#include <string>

class TestTerminalOutput : public ::testing::Test
{
protected:
    Terminal terminal;
    void SetUp() override
    {
        testing::internal::CaptureStdout();
    }

    void TearDown() override {}
};

TEST_F(TestTerminalOutput, display_message_no_newline)
{
    terminal.display_message("Hello World.", false);
    string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Hello World.");
}

TEST_F(TestTerminalOutput, display_message_with_newline)
{
    terminal.display_message("Hello World.", true);
    string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Hello World.\n");
}
