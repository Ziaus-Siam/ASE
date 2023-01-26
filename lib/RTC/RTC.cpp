/**
 * @file RTC.cpp
 * @author Muhammad Ziaus Siam (ziaus.siam@bjitgroup.com)
 * @brief 
 * @version 1.0
 * @date 2023-01-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <RTC.hpp>

time_t RTC::get_time()
{
    return time(0);
}