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

UserDatabase::UserDatabase(Terminal &in_terminal) : m_terminal(in_terminal)
{
    //
}

int UserDatabase::read_user_db()
{
    string line;
    m_user_database.clear();
    fstream file("data/UserDB.csv", ios::in);
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
        return 0;
    }
    else
    {
        m_terminal.display_message("Could not find User Database  file!!", true);
    }
    return 1;
}

user_data_t UserDatabase::get_user_data(string in_user_name)
{
    user_data_t user_data;
    for (int i = 0; i < m_user_database.size(); i++)
    {
        if (m_user_database[i].first == in_user_name)
        {
            user_data = m_user_database[i];
            break;
        }
    }

    if (user_data.first != in_user_name)
    {
        m_terminal.display_message("No such user registered.", true);
    }

    return user_data;
}

int UserDatabase::add_user(user_data_t in_user_data)
{
    m_user_database.push_back(in_user_data);
    return 0;
}

int UserDatabase::write_user_db(bool in_rewrite)
{
    ofstream file;
    string file_name = "data/UserDB.csv";
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
            int i = m_user_database.size()-1;
            file << m_user_database[i].first << ',' << m_user_database[i].second << endl;
        }
        file.close();
        return 0;
    }
    return 1;
}

int UserDatabase::register_new_user()
{
    m_terminal.display_message("Enter new user name: ", true);
    string user_name = m_terminal.get_input();
    if (user_name.size() > 10)
    {
        m_terminal.display_message("Max length for name is 10. Limit Exceeded.", true);
        return 1;
    }
    m_terminal.display_message("Enter new user id: ", true);
    string user_id = m_terminal.get_input();
    if (user_id.size() > 5)
    {
        m_terminal.display_message("Max length for ID is 5. Limit Exceeded.", true);
        return 1;
    }
    for (int i = 0; i < m_user_database.size(); i++)
    {
        if (m_user_database[i].second == user_id)
        {
            m_terminal.display_message("A user is already registered with this ID.", true);
            return 1;
        }
    }
    user_data_t user_data(user_name, user_id);
    add_user(user_data);
    write_user_db();
    m_terminal.display_message("Registration Succesfull.", true);
    return 0;
}

int UserDatabase::remove_user()
{
    m_terminal.display_message("Enter registered user name: ", true);
    string user_name = m_terminal.get_input();
    bool found = false;
    for (int i = 0; i < m_user_database.size(); i++)
    {
        if (m_user_database[i].first == user_name)
        {
            m_user_database.erase(m_user_database.begin() + i);
            found = true;
            break;
        }
    }
    if (!found)
    {
        m_terminal.display_message("No such user is registered in Database.", true);
        return 1;
    }
    write_user_db(true);
    return 0;
}

int UserDatabase::view_all_users()
{
    ofstream file;
    file.open("data/output.txt");
    if (file.is_open())
    {
        file << "REGISTERED USERS\n"
             << endl;
        file << "Employee ID   "
             << "NAME" << endl;
        for (int i = 0; i < m_user_database.size(); i++)
        {
            file << m_user_database[i].second;
            file << "         ";
            file << m_user_database[i].first << endl;
        }
    }
    else
    {
        m_terminal.display_message("Cannot find database!!", true);
        return 1;
    }
    return 0;
}