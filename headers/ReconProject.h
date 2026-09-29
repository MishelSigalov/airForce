#pragma once
#include "ScratchProject.h"
#include <Aircraft.h>
#include <vector>
using std::vector;

class ReconProject : public ScratchProject{  
    public:
        ReconProject(string name, string desc, int numOfAircraft,
                     string camera, string flightCourse, string startTime, string endTime, vector<Aircraft> aircraftList);
    private:
        string startTime;
        string endTime;
        vector<Aircraft> aircraftList;
};