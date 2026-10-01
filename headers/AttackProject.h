#pragma once
#include "Project.h"
#include "Aircraft.h"
#include "ScratchProject.h"
#include <vector>
using std::vector;

#define PREP_TIME_HOURS_ATTACK 10 // Minimum preparation time in hours

class AttackProject : public Project{  
    public:
        //regular constructor
        // Primary Field Constructor
    AttackProject(const std::string& name, 
                  const std::string& desc, 
                  int numOfAircraft,
                  const std::string& weaponry, 
                  const std::string& coordinates, 
                  const std::string& startTime, 
                  const std::string& endTime, 
                  const std::vector<Aircraft*>& aircraftList = {});

    // Delegate Constructor from ScratchProject
    AttackProject(const ScratchProject& scratchProject, 
                  const std::string& weaponry, 
                  const std::string& coordinates, 
                  const std::string& startTime, 
                  const std::string& endTime, 
                  const std::vector<Aircraft*>& aircraftList = {});

        void setAircraftList(vector<Aircraft*> aircraftList);
        void addAircraft(Aircraft* aircraft);

        void setStartTime(string newStartTime);
        void setEndTime(string newEndTime);

        int getId() const;
        string getStartTime() const;
        string getEndTime() const;
        const vector<Aircraft*>& getAircraftList() const;

        bool isReady() const override;

    private:
        int id; // only needed for attack or recon projects, not scratch projects
        string weaponry;
        string coordinates;
        string startTime;
        string endTime;
        vector<Aircraft*> aircraftList;

        static int nextId; // Static member to keep track of the next available ID
};