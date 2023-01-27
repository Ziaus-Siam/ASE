/**
 * @file admin_service.hpp
 * @author Muhammad Ziaus Siam (ziaus.siam@bjitgroup.com)
 * @brief
 * @version 1.0
 * @date 2023-01-26
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include <RTC.hpp>
#include <Terminal.hpp>
#include <UserDatabase.hpp>
#include <EntryLog.hpp>
#include <string>
#include <fstream>

using namespace std;

class AdminService
{
protected:

    bool m_authorized = false;

public:
    RTC &m_timer;
    Terminal &m_terminal;
    UserDatabase &m_userdb;
    EntryLog &m_entrylog;
    AdminService(RTC &, Terminal &, UserDatabase &, EntryLog &);
    void set_user_db_path(string in_path) { m_userdb.set_file_path(in_path); }
    void set_entrylog_db_path(string in_path) { m_entrylog.set_file_path(in_path); }
    
    int login();
    int logout();
    int show_menu();
    int load_database();
    int view_registered_users();
    int register_new_user();
    int remove_registered_user();
    int get_last_ten_logs();
    int run();

    friend bool spy_admin_login(AdminService in_AS);
};
