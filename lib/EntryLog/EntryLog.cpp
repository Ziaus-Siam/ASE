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
#include <fstream>

EntryLog::EntryLog()
{
}

int EntryLog::set_file_path(string in_path)
{
    m_file_path = in_path;
    return 0;
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
    int start_size = max((int)m_entry_log.size() - 10, 0);
    int end_size = m_entry_log.size();
    for (int i = start_size; i < end_size; i++)
    {
        string user_name = get<0>(m_entry_log[i]).first;
        string user_id = get<0>(m_entry_log[i]).second;
        time_t entry_time = get<1>(m_entry_log[i]);
        string converted_time = convert_time_to_string(entry_time);

        time_t exit_time = get<2>(m_entry_log[i]);
        string converted_time2 = convert_time_to_string(exit_time);

        time_t worked_time = get<3>(m_entry_log[i]);
        string converted_time3 = convert_worked_time_to_string(worked_time);

        string result = user_name + "  " + user_id + "  " + converted_time + "  " + converted_time2 + "  " + converted_time3 + "\n";
        output += result;
    }
    return output;
}

int EntryLog::load_database()
{

    ifstream file;
    string line;
    file.open(m_file_path);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            stringstream token(line);
            user_data_t user;
            string time1;
            string time2;
            string time3;
            getline(token, user.first, ',');
            getline(token, user.second, ',');
            getline(token, time1, ',');
            getline(token, time2, ',');
            getline(token, time3, ',');
            time_t t1 = stoll(time1, NULL, 10);
            time_t t2 = stoll(time2, NULL, 10);
            time_t t3 = stoll(time3, NULL, 10);
            entry_log_t entry(user, t1, t2, t3);
            m_entry_log.push_back(entry);
        }
    }
    else
    {
        return 1;
    }
    file.close();
    return 0;
}

int EntryLog::save_database(bool in_rewrite)
{
    ofstream file;
    if (in_rewrite)
    {
        file.open(m_file_path);
    }
    else
    {
        file.open(m_file_path, std::ios_base::app);
    }
    if (file.is_open())
    {
        if (in_rewrite)
        {
            for (int i = 0; i < m_entry_log.size(); i++)
            {
                file << get<0>(m_entry_log[i]).first << ',';
                file << get<0>(m_entry_log[i]).second << ',';
                file << get<1>(m_entry_log[i]) << ',';
                file << get<2>(m_entry_log[i]) << ',';
                file << get<3>(m_entry_log[i]) << "\n";
            }
        }
        else
        {
            int latest_entry = m_entry_log.size() - 1;
            file << get<0>(m_entry_log[latest_entry]).first << ',';
            file << get<0>(m_entry_log[latest_entry]).second << ',';
            file << get<1>(m_entry_log[latest_entry]) << ',';
            file << get<2>(m_entry_log[latest_entry]) << ',';
            file << get<3>(m_entry_log[latest_entry]) << "\n";
        }
    }
    else
    {
        return 1;
    }
    file.close();
    return 0;
}