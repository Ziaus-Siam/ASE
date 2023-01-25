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
#include <../helper/test_helper.hpp>

class TestUserDBOutput : public ::testing::Test
{
protected:
    Terminal terminal;
    UserDatabase *userdb;
    user_data_t user;

    void SetUp() override
    {
        UserDatabase st(terminal);
        userdb = &st;
        user.first = "Siam";
        user.second = "11527";
    }

    void TearDown() override
    {
    }
};

TEST_F(TestUserDBOutput, add_new_user)
{
    userdb->add_user(user);
    user_data_t result = userdb->get_user_data("Siam");
    ASSERT_EQ(user.first, result.first);
    ASSERT_EQ(user.second, result.second);
}

TEST_F(TestUserDBOutput, write_user_database)
{
    userdb->add_user(user);
    int result = userdb->write_user_db();
    ASSERT_EQ(result, 0);
    fstream file("data/UserDB.csv", ios::in);
    userdb->read_user_db();
    user_data_t data = userdb->get_user_data("Siam");
    ASSERT_EQ(data.first, user.first);
    ASSERT_EQ(data.second, user.second);
}

TEST_F(TestUserDBOutput, register_new_users)
{
    prepare_input("Siam\n11527");
    int x = userdb->register_new_user();
    user_data_t result = userdb->get_user_data("Siam");
    ASSERT_EQ(result.first, "Siam");
    ASSERT_EQ(result.second, "11527");
    ASSERT_EQ(x, 0);
}

TEST_F(TestUserDBOutput, delete_registered_users)
{
    prepare_input("Siam\n11527");
    userdb->register_new_user();
    prepare_input("Akram\n11530");
    userdb->register_new_user();
    prepare_input("Siam");
    int x = userdb->remove_user();
    ASSERT_EQ(x, 0);
    userdb->read_user_db();
    user_data_t result = userdb->get_user_data("Siam");
    ASSERT_NE(result.first, "Siam");
    ASSERT_NE(result.second, "11527");
}

TEST_F(TestUserDBOutput, view_registered_users)
{
    ofstream prep;
    prep.open("data/UserDB.csv");
    prep.clear();
    prep.close();

    ofstream valid_output;
    valid_output.open("data/valid_output.txt");
    valid_output << "REGISTERED USERS\n";
    valid_output << "\n";
    valid_output << "Employee ID   NAME\n";
    valid_output << "11530         Akram\n";
    valid_output << "11528         Jubaer\n";
    valid_output << "11529         Shishir\n";
    
    prepare_input("Akram\n11530");
    userdb->register_new_user();
    prepare_input("Jubaer\n11528");
    userdb->register_new_user();
    prepare_input("Shishir\n11529");
    userdb->register_new_user();
    int x = userdb->view_all_users();
    ASSERT_EQ(x, 0);

    ifstream check, outfile;
    check.open("data/valid_output.txt");
    outfile.open("data/output.txt");
    string line, valid_line;
    bool passed = true;
    while (getline(check,valid_line))
    {
        getline(outfile, line);
        if (valid_line != line)
        {
            passed = false;
            break;
        }
    }
    ASSERT_TRUE(passed);
}