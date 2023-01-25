/**
 * @file test_helper.hpp
 * @author Muhammad Ziaus Siam (ziaus.siam@bjitgroup.com)
 * @brief 
 * @version 1.0
 * @date 2023-01-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void prepare_input(string user_input)
{
    ofstream file;
    file.open("data/input.txt");
    file.clear();
    file << user_input;
    file.close();
}