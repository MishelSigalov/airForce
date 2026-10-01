#pragma once
#include "ScratchProject.h"
#include "Aircraft.h"
#include <vector>
#include <cmath>
using std::vector;

#define PREP_TIME_HOURS_RECON 3 // Minimum preparation time in hours

class ReconProject : public ScratchProject{  
    public:
        //regular constructor
        ReconProject(const string& name, const string& desc, int numOfAircraft,
                     const string& camera, const string& flightCourse, const string& startTime, const string& endTime, const vector<Aircraft*>& aircraftList);
        //contructor that creates a project based on a scratch project
        ReconProject(const ScratchProject& scratchProject, const string& startTime, const string& endTime, const vector<Aircraft*>& aircraftList);
        void setAircraftList(vector<Aircraft*> aircraftList);
        void addAircraft(Aircraft* aircraft);

        void setStartTime(string newStartTime);
        void setEndTime(string newEndTime);


        string getStartTime() const;
        string getEndTime() const;
        const vector<Aircraft*>& getAircraftList() const;
        int getId() const;

        bool isReady() const override;

    private:
        int id; // only needed for attack or recon projects, not scratch projects
        string startTime;
        string endTime;
        vector<Aircraft*> aircraftList;

        static int nextId; // Static member to keep track of the next available ID
};