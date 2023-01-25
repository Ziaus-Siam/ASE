/**
 * @file EntryLog.cpp
 * @author Muhammad Ziaus Siam (ziaus.siam@bjitgroup.com)
 * @brief
 * @version 1.0
 * @date 2023-01-25
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <EntryLog.hpp>
#include <sstream>
#include <iomanip>

EntryLog::EntryLog()
{
}

int EntryLog::create_log(user_data_t in_user_data, time_t in_time)
{
    int index = -1;
    bool entry_already_exists = false;

    for (int i = 0; i < m_entry_log.size(); i++)
    {
        if (in_user_data.second == get<0>(m_entry_log[i]).second)
        {
            entry_already_exists = true;
            index = i;
            break;
        }
    }

    if (entry_already_exists)
    {
        entry_log_t new_entry;
        get<0>(new_entry) = in_user_data;
        get<1>(new_entry) = get<1>(m_entry_log[index]);
        get<2>(new_entry) = in_time;
        get<3>(new_entry) = get_worked_time(get<1>(new_entry), get<2>(new_entry));
        m_entry_log.push_back(new_entry);
    }
    else
    {
        entry_log_t new_entry(in_user_data, in_time, in_time, 0);
        m_entry_log.push_back(new_entry);
    }
    return 0;
}

time_t EntryLog::get_worked_time(time_t in_time1, time_t in_time2)
{
    time_t diff = in_time2 - in_time1;
    return diff;
}

string EntryLog::convert_time_to_string(time_t in_time)
{
    tm *ltm = localtime(&in_time);
    ltm->tm_year += 1900;
    ltm->tm_mon += 1;
    stringstream ss;
    ss << setw(2) << setfill('0') << ltm->tm_hour;
    ss << ':';
    ss << setw(2) << setfill('0') << ltm->tm_min;
    string output;
    ss >> output;
    return output;
}

string EntryLog::convert_worked_time_to_string(time_t in_time)
{
    tm *ltm = localtime(&in_time);
    ltm->tm_year -= 70;
    ltm->tm_mday -= 1;
    ltm->tm_hour -= 6;
    stringstream ss;
    ss << setw(2) << setfill('0') << ltm->tm_hour;
    ss << ':';
    ss << setw(2) << setfill('0') << ltm->tm_min;
    string output;
    ss >> output;
    return output;
}

string EntryLog::get_last_ten_logs()
{
    string output;
    for (int i = m_entry_log.size() - 10; i < m_entry_log.size() - 1; i++)
    {
        string user_name = get<0>(m_entry_log[i]).first;
        string user_id = get<0>(m_entry_log[i]).second;
        time_t entry_time = get<1>(m_entry_log[i]);
        string converted_time = convert_time_to_string(entry_time);

        time_t exit_time = get<2>(m_entry_log[i]);
        string converted_time2 = convert_time_to_string(exit_time);

        time_t worked_time = get<3>(m_entry_log[i]);
        string converted_time3 = convert_worked_time_to_string(worked_time);

        string result = user_name + "  " + user_id + "  " + converted_time +  "  " + converted_time2 +  "  " + converted_time3 + "\n";
        output += result;
    }
    return output;
}