#pragma once
#include "Project.h"
#include "Aircraft.h"
#include "ScratchProject.h"
#include <vector>
using std::vector;

class AttackProject : public Project{  
    public:
        //regular constructor
        AttackProject(string name, string desc, int numOfAircraft,
                      string weaponry, string coordinates, string startTime, string endTime, vector<Aircraft> aircraftList);
        //contructor that creates a project based on a scratch project
        AttackProject(ScratchProject scratchProject, string weaponry, string coordinates, string startTime, string endTime, vector<Aircraft> aircraftList);
        void setAircraftList(vector<Aircraft> aircraftList);
        void addAircraft(Aircraft aircraft);

    private:
        string weaponry;
        string coordinates;
        string startTime;
        string endTime;
        vector<Aircraft> aircraftList;
};