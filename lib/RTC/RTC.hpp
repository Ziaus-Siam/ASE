/**
 * @file RTC.hpp
 * @author Muhammad Ziaus Siam (ziaus.siam@bjitgroup.com)
 * @brief 
 * @version 1.0
 * @date 2023-01-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <base_RTC.hpp>
#include <ctime>

class RTC : public BaseRTC
{
public:
    time_t get_time();
};
