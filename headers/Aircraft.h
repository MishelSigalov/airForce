#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

#define HOUR_START_INDEX 0
#define MINUTE_START_INDEX 3

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