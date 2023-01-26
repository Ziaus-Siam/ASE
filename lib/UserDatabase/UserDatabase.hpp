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
#include <base_db.hpp>

using namespace std;

class UserDatabase : public Database
{
private:
    string m_file_path;
    vector<user_data_t> m_user_database;

public:
    UserDatabase();
    int load_database();
    int save_database(bool in_rewrite = false);
    int set_file_path(string in_path);
    user_data_t get_user_data(string in_user_name);
    int add_user(user_data_t in_user_data);
    int register_new_user(string in_user_name, string in_user_id);
    int remove_user(string in_user_id);
    string view_all_users();
};
