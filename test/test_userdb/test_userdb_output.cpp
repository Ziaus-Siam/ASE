/**
 * @file test_storage_output.cpp
 * @author Muhammad Ziaus Siam (ziaus.siam@bjitgroup.com)
 * @brief
 * @version 1.0
 * @date 2023-01-24
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <gmock/gmock.h>
#include <Terminal.hpp>
#include <UserDatabase.hpp>
#include <../../include/typedefs.hpp>
#include <fstream>
#include <sstream>
#include <cstdio>

class TestUserDBOutput : public ::testing::Test
{
protected:
    UserDatabase userdb;
    user_data_t user;

    void SetUp() override
    {
        user.first = "Siam";
        user.second = "11527";
        userdb.set_file_path("data/UserDB.csv");
    }

    void TearDown() override
    {
    }
};

TEST_F(TestUserDBOutput, add_new_user)
{
    userdb.add_user(user);
    user_data_t result = userdb.get_user_data("11527");
    ASSERT_EQ(user.first, result.first);
    ASSERT_EQ(user.second, result.second);
}

TEST_F(TestUserDBOutput, write_user_database)
{
    userdb.add_user(user);
    int result = userdb.save_database();
    ASSERT_EQ(result, 0);
    userdb.load_database();
    user_data_t data = userdb.get_user_data("11527");
    ASSERT_EQ(data.first, user.first);
    ASSERT_EQ(data.second, user.second);
}

TEST_F(TestUserDBOutput, register_new_users)
{
    int x = userdb.register_new_user("Siam", "11527");
    user_data_t result = userdb.get_user_data("11527");
    ASSERT_EQ(result.first, "Siam");
    ASSERT_EQ(result.second, "11527");
    ASSERT_EQ(x, 0);
}

TEST_F(TestUserDBOutput, delete_registered_users)
{
    userdb.register_new_user("Siam", "11527");
    userdb.register_new_user("Akram", "11530");
    int x = userdb.remove_user("11527");
    ASSERT_EQ(x, 0);
    userdb.load_database();
    user_data_t result = userdb.get_user_data("11527");
    ASSERT_NE(result.first, "Siam");
    ASSERT_NE(result.second, "11527");
    ASSERT_EQ(result.second, "");
    ASSERT_EQ(result.second, "");
}

TEST_F(TestUserDBOutput, view_registered_users)
{
    ofstream prep;
    prep.open("data/UserDB.csv");
    prep.clear();
    prep.close();

    string valid_output;
    valid_output = "REGISTERED USERS\n\n";
    valid_output += "Employee ID   NAME\n";
    valid_output += "11530         Akram\n";
    valid_output += "11528         Jubaer\n";
    valid_output += "11529         Shishir\n";

    userdb.register_new_user("Akram", "11530");
    userdb.register_new_user("Jubaer", "11528");
    userdb.register_new_user("Shishir", "11529");
    string x = userdb.view_all_users();
    ASSERT_EQ(x, valid_output);
}