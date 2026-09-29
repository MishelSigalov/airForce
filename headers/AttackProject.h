#pragma once
#include "Project.h"
#include "Aircraft.h"
#include <vector>
using std::vector;

class AttackProject : public Project{  
    public:
        AttackProject(string name, string desc, int numOfAircraft,
                      string weaponry, string coordinates, string startTime, string endTime, vector<Aircraft> aircraftList);
    private:
        string weaponry;
        string coordinates;
        string startTime;
        string endTime;
        vector<Aircraft> aircraftList;
};