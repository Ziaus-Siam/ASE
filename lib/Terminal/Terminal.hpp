/**
 * @file Terminal.hpp
 * @author Muhammad Ziaus Siam (ziaus.siam@bjitgroup.com)
 * @brief Header file for the terminal interface.
 * @version 1.0
 * @date 2023-01-23
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include <string>

using namespace std;

class Terminal
{
public:
    int display_message(string in_msg, bool in_newline = false, bool rewrite = true);
    string get_input();
};
