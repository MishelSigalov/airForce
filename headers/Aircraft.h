#pragma once

#include <string>
#include <vector>
#include <ctime>

using std::string;
using std::vector;
using std::stoi;

#define YEAR_START_INDEX 0
#define MONTH_START_INDEX 5
#define DAY_START_INDEX 8
#define HOUR_START_INDEX 11
#define MINUTE_START_INDEX 14

#define SECONDS_IN_A_MINUTE 60

class Aircraft {  
    public:
        Aircraft(int id);
        int getId() const;
        bool isAvailable(string startTime, string endTime) const;
        void assign(string startTime, string endTime, int projectId);
        void unassign(int projectId);


        
    private:
        int id;
        int numberofProjectsAssigned;
        vector<int> ids;
        vector<string> startTimes;
        vector<string> endTimes;
  
        // Helper function to convert time string to minutes from midnight for comparison
        int timeToMinutes(string time) const;
};