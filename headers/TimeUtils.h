#pragma once

#include <string>
#include <iostream>
#include <ctime>

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::to_string;

#define YEAR_START_INDEX 0
#define MONTH_START_INDEX 5
#define DAY_START_INDEX 8
#define HOUR_START_INDEX 11
#define MINUTE_START_INDEX 14

#define SECONDS_IN_A_MINUTE 60

namespace TimeUtils {
    // Converts "YYYY-MM-DD HH:MM" to total minutes since Unix epoch
    int timeToMinutes(const string time);

    // Function to get a valid time input from the user in the format "YYYY-MM-DD HH:MM".
    string getTime();
    // Helper to get maximum valid days for a given month
    int getDaysInMonth(int month);

}