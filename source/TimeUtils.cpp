#include "TimeUtils.h"
#include <string>
#include <ctime>

namespace TimeUtils {
    
    int timeToMinutes(const string time) {
        if (time.length() < 16) {
            cout << "Error: Time string is too short to parse." << endl;
            return -1; // Basic length guard
        }

        std::tm tm = {};
        tm.tm_year = std::stoi(time.substr(YEAR_START_INDEX, 4)) - 1900;
        tm.tm_mon  = std::stoi(time.substr(MONTH_START_INDEX, 2)) - 1;
        tm.tm_mday = std::stoi(time.substr(DAY_START_INDEX, 2));
        tm.tm_hour = std::stoi(time.substr(HOUR_START_INDEX, 2));
        tm.tm_min  = std::stoi(time.substr(MINUTE_START_INDEX, 2));

        std::time_t timeInSeconds = std::mktime(&tm);
        return static_cast<int>(timeInSeconds / SECONDS_IN_A_MINUTE);
    }




    
    string getTime(char timeType) {
        int year = 0, month = 0, day = 0, hour = 0, minute = 0, maxDays = 0;

        if(timeType == 's') {
            cout << "----Start Time----" << endl;
        } 
        else if(timeType == 'e') {
            cout << "----End Time----" << endl;
        }

        // 1. Validate Year
        while (true) {
            cout << "Enter Year (2026-2100): ";
            if (cin >> year && year > 2025 && year <= 2100) {
                break;
            }
            cout << "Invalid year! Please enter a year between 2026 and 2100.\n";
        }

        // 2. Validate Month
        while (true) {
            cout << "Enter Month (1-12): ";
            if (cin >> month && month >= 1 && month <= 12) {
                break;
            }
            cout << "Invalid month! Please enter a number between 1 and 12.\n";

        }

        // 3. Validate Day (Checks against month length)
        maxDays = getDaysInMonth(month);
        while (true) {
            cout << "Enter Day (1-" << maxDays << "): ";
            if (cin >> day && day >= 1 && day <= maxDays) {
                break;
            }
            cout << "Invalid day for this month! Please enter a valid day.\n";
        }

        // 4. Validate Hour & Minute (HH:MM)
        while (true) {
            string timeStr;
            cout << "Enter Hour (HH:MM): ";
            cin >> timeStr;

            // Ensure length and colon separator format ("HH:MM")
            if (timeStr.length() == 5 && timeStr[2] == ':') {
                try {
                    hour = std::stoi(timeStr.substr(0, 2)); //0-1 is the hour
                    minute = std::stoi(timeStr.substr(3, 2));//3-4 is the minute

                    if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59) {
                        break; // Valid time entered
                    }
                } catch (...) {
                    // Catches non-numeric string conversions
                }
            }
            cout << "Invalid time format! Enter time as HH:MM (e.g. 14:30 or 09:05)." << endl;
        }

        // Manual zero-padding
        string yearStr   = std::to_string(year);
        string monthStr  = (month < 10 ? "0" : "") + to_string(month);
        string dayStr    = (day < 10 ? "0" : "") + to_string(day);
        string hourStr   = (hour < 10 ? "0" : "") + to_string(hour);
        string minStr    = (minute < 10 ? "0" : "") + to_string(minute);

        // Formats into standardized "YYYY-MM-DD HH:MM"
        return yearStr + "-" + monthStr + "-" + dayStr + " " + hourStr + ":" + minStr;
    }


    
    int getDaysInMonth(int month) {
        switch (month) {
            //April, June, September, November have 30 days
            case 4: case 6: case 9: case 11:
                return 30;
            //February has 28 days (ignoring leap years for simplicity)
            case 2:
                return 28;
            //All other months have 31 days
            default:
                return 31;
        }
    }
    

    bool hasEnoughPrepTime(int prepHours, string startTimeStr) {
        int startMinutes = timeToMinutes(startTimeStr);
        if (startMinutes == -1) return false;

        // Get current system time in minutes since Epoch
        std::time_t nowSeconds = std::time(nullptr);
        int nowMinutes = static_cast<int>(nowSeconds / 60);

        int requiredBufferMinutes = prepHours * 60;

        // Check if remaining minutes before start meets the required time, also of course, the start time must be in the future
        return (startMinutes - nowMinutes) >= requiredBufferMinutes;
    }


} // namespace Utils