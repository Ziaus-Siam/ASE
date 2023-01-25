/**
 * @file typedefs.hpp
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
#include <tuple>
#include <queue>
#include <ctime>

using namespace std;

typedef pair<string, string> user_data_t;
typedef tuple<user_data_t, time_t, time_t, time_t> entry_log_t;