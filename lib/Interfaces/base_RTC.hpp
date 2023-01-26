/**
 * @file base_RTC.hpp
 * @author Muhammad Ziaus Siam (ziaus.siam@bjitgroup.com)
 * @brief 
 * @version 1.0
 * @date 2023-01-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

using namespace std;

class BaseRTC
{
public:
    virtual long long get_time() = 0;
};