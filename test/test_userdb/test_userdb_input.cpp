/**
 * @file test_storage_input.cpp
 * @author Muhammad Ziaus Siam (ziaus.siam@bjitgroup.com)
 * @brief Implementation of Non-volatile memory
 * @version 1.0
 * @date 2023-01-23
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

class TestUserDBInput : public ::testing::Test
{
protected:
    UserDatabase userdb;

    void SetUp() override
    {
        fstream file("data/UserDB.csv", ios::out);
        file << "Siam,11527" << endl;
        file.close();
        userdb.set_file_path("data/UserDB.csv");
    }

    void TearDown() override
    {
    }
};

TEST_F(TestUserDBInput, read_user_database)
{
    user_data_t user_data;
    ASSERT_EQ(userdb.load_database(), 0);
}

TEST_F(TestUserDBInput, get_user_data)
{
    user_data_t user_data;
    userdb.load_database();
    user_data = userdb.get_user_data("11527");
    ASSERT_EQ(user_data.first, "Siam");
    ASSERT_EQ(user_data.second, "11527");
}
