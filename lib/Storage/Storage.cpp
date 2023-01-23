/**
 * @file Storage.cpp
 * @author Muhammad Ziaus Siam (ziaus.siam@bjitgroup.com)
 * @brief Implementation of non-volatile memory
 * @version 1.0
 * @date 2023-01-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Storage.hpp>
#include <fstream>
#include <sstream>

using namespace std;

Storage::Storage(Terminal &in_terminal) : m_terminal(in_terminal)
{
    //
}

void Storage::read()
{
    string line;
    fstream file("UserDB.csv", ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            stringstream token(line);
            string user_name;
            string password;
            getline(token, user_name, ',');
            getline(token, password, ',');
            m_user_database[user_name] = password;
        }
    }
    else
    {
        m_terminal.display_message("Could not find User Database  file!!", true);
    }
}