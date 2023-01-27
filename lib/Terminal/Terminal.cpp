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
#include <fstream>

using namespace std;

#if 0

int Terminal::display_message(string in_msg, bool in_newline, bool rewrite)
{
    ofstream file;
    if (rewrite)
    {
        file.open("data/output.txt");
    }
    else
    {
        file.open("data/output.txt", std::ios_base::app);
    }
    if (file.is_open())
    {
        if (in_newline)
        {
            file << in_msg << endl;
        }
        else
        {
            file << in_msg;
        }
    }
    file.close();
    return 0;
}

string Terminal::get_input()
{
    string val, line;
    ifstream file;
    ofstream temp;
    file.open("data/input.txt");
    temp.open("data/temp.txt");
    if (file.is_open())
    {
        getline(file, val);
    }
    else
    {
        val = "";
    }
    while (getline(file, line))
    {
        temp << line;
    }
    temp.close();
    file.close();
    remove("data/input.txt");
    rename("data/temp.txt", "data/input.txt");
    return val;
}
#else

int Terminal::display_message(string in_msg, bool in_newline, bool rewrite)
{
    if (in_newline)
    {
        cout  << ' ' << in_msg << endl;
    }
    else
    {
        cout  << ' '  << in_msg;
    }

    return 0;
}


string Terminal::get_input()
{

    string output;
    getline(cin, output);
    return output;
}

#endif