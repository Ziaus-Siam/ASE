/**
 * @file UserDatabase.cpp
 * @author Muhammad Ziaus Siam (ziaus.siam@bjitgroup.com)
 * @brief Implementation of non-volatile memory
 * @version 1.0
 * @date 2023-01-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <UserDatabase.hpp>
#include <fstream>
#include <sstream>

using namespace std;

UserDatabase::UserDatabase()
{
    //
}

int UserDatabase::set_file_path(string in_path)
{
    m_file_path = in_path;
    return 0;
}

int UserDatabase::load_database()
{
    string line;
    m_user_database.clear();
    ifstream file;
    file.open(m_file_path);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            stringstream token(line);
            user_data_t user_data;
            getline(token, user_data.first, ',');
            getline(token, user_data.second, ',');
            m_user_database.push_back(user_data);
        }
        file.close();
    }
    else
    {
        cout << "here\n";
        return 1;
    }
    return 0;
}

user_data_t UserDatabase::get_user_data(string in_user_id)
{
    user_data_t user_data;
    for (int i = 0; i < m_user_database.size(); i++)
    {
        if (m_user_database[i].second == in_user_id)
        {
            user_data = m_user_database[i];
            break;
        }
    }
    return user_data;
}

int UserDatabase::add_user(user_data_t in_user_data)
{
    m_user_database.push_back(in_user_data);
    return 0;
}

int UserDatabase::save_database(bool in_rewrite)
{
    ofstream file;
    string file_name = m_file_path;
    if (in_rewrite)
    {
        file.open(file_name);
    }
    else
    {
        file.open(file_name, std::ios_base::app);
    }

    if (file.is_open())
    {
        if (in_rewrite)
        {
            for (int i = 0; i < m_user_database.size(); i++)
            {
                file << m_user_database[i].first << ',' << m_user_database[i].second << endl;
            }
        }
        else
        {
            int i = m_user_database.size() - 1;
            file << m_user_database[i].first << ',' << m_user_database[i].second << endl;
        }
        file.close();
        return 0;
    }
    return 1;
}

int UserDatabase::register_new_user(string in_user_name, string in_user_id)
{
    for (int i = 0; i < m_user_database.size(); i++)
    {
        if (m_user_database[i].second == in_user_id)
        {
            return 1;
        }
    }
    user_data_t user_data(in_user_name, in_user_id);
    add_user(user_data);
    save_database();
    return 0;
}

int UserDatabase::remove_user(string in_user_id)
{
    bool found = false;
    for (int i = 0; i < m_user_database.size(); i++)
    {
        if (m_user_database[i].second == in_user_id)
        {
            m_user_database.erase(m_user_database.begin() + i);
            found = true;
            break;
        }
    }
    if (!found)
    {
        return 1;
    }
    save_database(true);
    return 0;
}

string UserDatabase::view_all_users()
{
    string output;
    output = "REGISTERED USERS\n\n";
    output += "Employee ID   ";
    output += "NAME\n";
    for (int i = 0; i < m_user_database.size(); i++)
    {
        output += m_user_database[i].second;
        output += "         ";
        output += m_user_database[i].first;
        output += "\n";
    }
    return output;
}