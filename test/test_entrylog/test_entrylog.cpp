/**
 * @file test_entrylog.cpp
 * @author Muhammad Ziaus Siam (ziaus.siam@bjitgroup.com)
 * @brief
 * @version 1.0
 * @date 2023-01-25
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <gmock/gmock.h>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <../../include/typedefs.hpp>
#include <Terminal.hpp>
#include <UserDatabase.hpp>
#include <EntryLog.hpp>

entry_log_t spy_get_last_entry(EntryLog &in_entrylog)
{
    int loc = in_entrylog.m_entry_log.size() - 1;
    return in_entrylog.m_entry_log[loc];
}

class TestEntryLog : public ::testing::Test
{
protected:
    EntryLog entrylog;

    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(TestEntryLog, add_a_new_entry)
{
    time_t now = time(0);
    user_data_t user_data("Siam", "11527");
    int x = entrylog.create_log(user_data, now);
    EXPECT_EQ(x, 0);
    entry_log_t result = spy_get_last_entry(entrylog);
    entry_log_t answer(user_data, now, now, 0);
    ASSERT_EQ(get<0>(result), get<0>(answer));
    ASSERT_EQ(get<1>(result), get<1>(answer));
    ASSERT_EQ(get<2>(result), get<2>(answer));
    ASSERT_EQ(get<3>(result), get<3>(answer));
}

TEST_F(TestEntryLog, calculate_time_difference)
{
    time_t now1 = time(0);
    time_t now2 = now1 + 4 * 60;
    time_t result = entrylog.get_worked_time(now1, now2);
    EXPECT_EQ(result, now2 - now1);
}

TEST_F(TestEntryLog, add_to_existing_entry)
{
    time_t now1 = time(0);
    user_data_t user_data("Siam", "11527");
    entrylog.create_log(user_data, now1);

    time_t now2 = now1 + 4 * 60;
    int x = entrylog.create_log(user_data, now2);
    EXPECT_EQ(x, 0);

    entry_log_t result = spy_get_last_entry(entrylog);
    entry_log_t answer(user_data, now1, now2, 4 * 60);

    ASSERT_EQ(get<0>(result), get<0>(answer));
    ASSERT_EQ(get<1>(result), get<1>(answer));
    ASSERT_EQ(get<2>(result), get<2>(answer));
    ASSERT_EQ(get<3>(result), get<3>(answer));
}

TEST_F(TestEntryLog, time_converstion_to_string)
{
    time_t now1 = 1674653125;
    string output = entrylog.convert_time_to_string(now1);
    ASSERT_EQ(output, "19:25");
}

TEST_F(TestEntryLog, worked_time_converstion_to_string)
{
    time_t now1 = 20*60;
    string output = entrylog.convert_worked_time_to_string(now1);
    ASSERT_EQ(output, "00:20");
}

TEST_F(TestEntryLog, show_the_last_ten_logs)
{
    string answer;
    answer = "Siam  11527  19:25  20:05  00:40\n";
    answer += "Siam  11527  19:25  20:25  01:00\n";
    answer += "Siam  11527  19:25  20:45  01:20\n";
    answer += "Siam  11527  19:25  21:05  01:40\n";
    answer += "Siam  11527  19:25  21:25  02:00\n";
    answer += "Siam  11527  19:25  21:45  02:20\n";
    answer += "Siam  11527  19:25  22:05  02:40\n";
    answer += "Siam  11527  19:25  22:25  03:00\n";
    answer += "Siam  11527  19:25  22:45  03:20\n";
    time_t now1 = 1674653125;
    time_t temp = now1;
    user_data_t user_data("Siam", "11527");
    for (int i = 0; i < 12; i++)
    {
        entrylog.create_log(user_data, temp);
        temp += 20*60;
    }
    string result = entrylog.get_last_ten_logs();
    cout << result;
    ASSERT_EQ(result, answer);
}