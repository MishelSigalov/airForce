#pragma once
#include "ScratchProject.h"
#include "Aircraft.h"
#include <vector>
using std::vector;

class ReconProject : public ScratchProject{  
    public:
        //regular constructor
        ReconProject(string name, string desc, int numOfAircraft,
                     string camera, string flightCourse, string startTime, string endTime, vector<Aircraft> aircraftList);
        //contructor that creates a project based on a scratch project
        ReconProject(ScratchProject scratchProject, string startTime, string endTime, vector<Aircraft> aircraftList);
        void setAircraftList(vector<Aircraft> aircraftList);
        void addAircraft(Aircraft aircraft);
    private:
        string startTime;
        string endTime;
        vector<Aircraft> aircraftList;
};