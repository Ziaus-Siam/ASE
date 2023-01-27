/**
 * @file admin_service.cpp
 * @author Muhammad Ziaus Siam (ziaus.siam@bjitgroup.com)
 * @brief
 * @version 1.0
 * @date 2023-01-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <admin_service.hpp>
#include <iostream>
// #include <conio.h>

using namespace std;

AdminService::AdminService(RTC &in_timer, Terminal &in_terminal, UserDatabase &in_userdb, EntryLog &in_entrylog)
    : m_timer(in_timer),
      m_terminal(in_terminal),
      m_userdb(in_userdb),
      m_entrylog(in_entrylog)
{
    //
}

int AdminService::login()
{
    m_terminal.display_message("Enter Admin User Name: ", false, true);
    string admin_name = m_terminal.get_input();
    m_terminal.display_message("Enter Admin Password: ", false, false);
    string admin_ID = m_terminal.get_input();

    if (admin_name == "admin" && admin_ID == "admin")
    {
        m_authorized = true;
    }
    else
    {
        m_authorized = false;
        m_terminal.display_message("Wrong username or password", true);

        return 1;
    }
    return 0;
}

int AdminService::logout()
{
    m_authorized = false;
    m_terminal.display_message("Admin logged out.", true, true);

    return 0;
}

int AdminService::show_menu()
{

    m_terminal.display_message("\nAdmin Menu:", true, true);
    m_terminal.display_message("\t1. View registered users.", true, false);
    m_terminal.display_message("\t2. Register new user.", true, false);
    m_terminal.display_message("\t3. Delete registered user.", true, false);
    m_terminal.display_message("\t4. Show last 10 entry logs.", true, false);
    m_terminal.display_message("\t5. Exit.\n", true, false);
    return 0;
}

int AdminService::load_database()
{
    m_userdb.load_database();
    m_entrylog.load_database();

    return 0;
}

int AdminService::view_registered_users()
{
    string output = m_userdb.view_all_users();
    m_terminal.display_message(output, false, true);

    return 0;
}

int AdminService::register_new_user()
{
    m_terminal.display_message("Enter user name (Max 11 letters): ", false, true);
    string user_name = m_terminal.get_input();
    m_terminal.display_message("Enter user ID (Max 5 digits)    : ", false, false);
    string user_ID = m_terminal.get_input();
    bool error = false;
    if (user_name.size() > 10)
    {
        m_terminal.display_message("Max allowed size for user name is 10. Limit exceeded.", true, false);
        error = true;
    }

    if (user_ID.size() > 5)
    {
        m_terminal.display_message("Max allowed size for user ID is 5. Limit exceeded.", true, false);
        error = true;
    }
    if (error)
    {
        return 1;
    }
    int res = m_userdb.register_new_user(user_name, user_ID);
    if (res == 0)
    {
        m_terminal.display_message("Registration Successful.", true, false);
    }
    else
    {
        m_terminal.display_message("User already registered.", true, false);
    }

    return 0;
}

int AdminService::remove_registered_user()
{
    m_terminal.display_message("Enter user id to remove.", true, true);
    string user_ID = m_terminal.get_input();
    int res = m_userdb.remove_user(user_ID);

    if (res == 0)
    {
        m_terminal.display_message("User removed from database.", true, false);
    }
    else
    {
        m_terminal.display_message("User not found.", true, false);
    }

    return 0;
}

int AdminService::get_last_ten_logs()
{
    string output = m_entrylog.get_last_ten_logs();
    m_terminal.display_message(output, false, true);

    return 0;
}

int AdminService::run()
{
    login();
    while (m_authorized)
    {
        show_menu();
        m_terminal.display_message("Option: ",false);
        string choice = m_terminal.get_input();
        if (choice == "1")
        {
            view_registered_users();
        }
        else if (choice == "2")
        {
            register_new_user();
        }
        else if (choice == "3")
        {
            remove_registered_user();
        }
        else if (choice == "4")
        {
            get_last_ten_logs();
        }
        else if (choice == "5")
        {
            logout();
            break;
        }

        m_terminal.display_message("\nPress Enter to continue.\n", true, false);
        cin.get();
    }

    return true;
}