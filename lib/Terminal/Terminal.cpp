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
    string val,line;
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
    while (getline(file,line))
    {
        temp << line;
    }
    temp.close();
    file.close();
    remove("data/input.txt");
    rename("data/temp.txt","data/input.txt");
    return val;
}