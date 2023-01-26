/**
 * @file base_db.hpp
 * @author Muhammad Ziaus Siam (ziaus.siam@bjitgroup.com)
 * @brief 
 * @version 1.0
 * @date 2023-01-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once
#include <string>

using namespace std;

class Database
{
public:
    virtual int load_database() = 0;
    virtual int save_database(bool in_rewrite = false) = 0;
    virtual int set_file_path(string in_path) = 0;
};
