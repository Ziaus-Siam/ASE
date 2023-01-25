/**
 * @file UserDatabase.hpp
 * @author Muhammad Ziaus Siam (ziaus.siam@bjitgroup.com)
 * @brief Header file for implementation of non-volatile memory
 * @version 1.0
 * @date 2023-01-23
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include <unordered_map>
#include <string>
#include <Terminal.hpp>
#include <../../include/typedefs.hpp>
#include <vector>
#include <iostream>

using namespace std;

class UserDatabase
{
private:
    vector<user_data_t> m_user_database;
    Terminal &m_terminal;

public:
    UserDatabase(Terminal &in_terminal);
    int read_user_db();
    user_data_t get_user_data(string in_user_name);
    int add_user(user_data_t in_user_data);
    int write_user_db(bool in_rewrite = false);
    int register_new_user();
    int remove_user();
    int view_all_users();
};
