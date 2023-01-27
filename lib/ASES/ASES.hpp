/**
 * @file ASES.hpp
 * @author Muhammad Ziaus Siam (ziaus.siam@bjitgroup.com)
 * @brief 
 * @version 1.0
 * @date 2023-01-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <Terminal.hpp>
#include <RTC.hpp>
#include <UserDatabase.hpp>
#include <EntryLog.hpp>
#include <admin_service.hpp>
#include <string>

using namespace std;

class ASES
{
private:
    Terminal m_terminal;
    RTC m_timer;
    UserDatabase m_userdb;
    EntryLog m_entrylog;
public:
    int run();
};