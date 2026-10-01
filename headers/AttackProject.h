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
        int getId() const;
        string getStartTime() const;
        string getEndTime() const;
        const vector<Aircraft>& getAircraftList() const;

    private:
        int id; // only needed for attack or recon projects, not scratch projects
        string weaponry;
        string coordinates;
        string startTime;
        string endTime;
        vector<Aircraft> aircraftList;

        static int nextId; // Static member to keep track of the next available ID
};