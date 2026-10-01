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
        string getStartTime() const;
        string getEndTime() const;
        const vector<Aircraft>& getAircraftList() const;
        int getId() const;

    private:
        int id; // only needed for attack or recon projects, not scratch projects
        string startTime;
        string endTime;
        vector<Aircraft> aircraftList;

        static int nextId; // Static member to keep track of the next available ID
};