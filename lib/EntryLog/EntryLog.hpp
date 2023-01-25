/**
 * @file EntryLog.hpp
 * @author Muhammad Ziaus Siam (ziaus.siam@bjitgroup.com)
 * @brief
 * @version 1.0
 * @date 2023-01-25
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <ctime>
#include <Terminal.hpp>
#include <UserDatabase.hpp>
#include <RTC.hpp>
#include <RFID.hpp>
#include <../../include/typedefs.hpp>

using namespace std;

class EntryLog
{
private:
    vector<entry_log_t> m_entry_log;
public:
    EntryLog();
    int create_log(user_data_t in_user_data, time_t in_time);
    time_t get_worked_time(time_t in_time1, time_t in_time2);
    string get_last_ten_logs();
    string convert_time_to_string(time_t in_time);
    string convert_worked_time_to_string(time_t in_time);

    friend entry_log_t spy_get_last_entry(EntryLog &in_entrylog);
};
