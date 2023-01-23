/**
 * @file Terminal.cpp
 * @author Muhammad Ziaus Siam (ziaus.siam@bjitgroup.com)
 * @brief Implementation of the Terminal interface.
 * @version 1.0
 * @date 2023-01-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Terminal.hpp>
#include <iostream>

using namespace std;

void Terminal::display_message(string in_msg, bool in_newline)
{
    if (in_newline)
    {
        cout << in_msg << endl;
    }
    else
    {
        cout << in_msg;
    }
}

string Terminal::get_input()
{
    string msg;
    cin >> msg;
    return msg;
}