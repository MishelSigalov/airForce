#pragma once

#include "TimeUtils.h"
#include <string>
#include <vector>
#include <ctime>

using std::string;
using std::vector;
using std::stoi;



class Aircraft {  
    public:
        Aircraft(int id);
        int getId() const;
        bool isAvailable(string startTime, string endTime, int projectId = -1) const;
        void assign(string startTime, string endTime, int projectId);
        void unassign(int projectId);


        
    private:
        int id;
        int numberofProjectsAssigned;
        vector<int> ids;
        vector<string> startTimes;
        vector<string> endTimes;

};