/**
 * @file Storage.hpp
 * @author Muhammad Ziaus Siam (ziaus.siam@bjitgroup.com)
 * @brief Header file for implementation of non-volatile memory
 * @version 1.0
 * @date 2023-01-23
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include <unordered_map>
#include <string>
#include <Terminal.hpp>

using namespace std;

class Storage
{
private:
    unordered_map<string, string> m_user_database;
    Terminal &m_terminal;

public:
    Storage(Terminal &in_terminal);
    void read();
};
