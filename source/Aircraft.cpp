#include "Aircraft.h"


Aircraft::Aircraft(int id) : id(id)
{
    this->numberofProjectsAssigned = 0; // Set the initial number of projects assigned to 0
}

int Aircraft::getId() const
{
    return id;
}


bool Aircraft::isAvailable(string startTime, string endTime, int projectId) const { //set the projectId to -1 by default, meaning no project is being updated
    // 60-minute maintenance window
    int requestedStart = TimeUtils::timeToMinutes(startTime) - 60; 
    int requestedEnd   = TimeUtils::timeToMinutes(endTime) + 60; 

    for (size_t i = 0; i < this->ids.size(); i++) {
        // Skip the project being updated if projectId is provided
        if (projectId != -1 && this->ids[i] == projectId) {
            continue;
        }
        int bookedStart = TimeUtils::timeToMinutes(this->startTimes[i]);
        int bookedEnd   = TimeUtils::timeToMinutes(this->endTimes[i]);

        if (requestedStart < bookedEnd && bookedStart < requestedEnd) {
            return false; // Time collision
        }
    }
    return true;
}

void Aircraft::assign(string startTime, string endTime, int projectId) {
    this->numberofProjectsAssigned++;
    this->ids.push_back(projectId);
    this->startTimes.push_back(startTime);
    this->endTimes.push_back(endTime);
}

void Aircraft::unassign(int projectId) {
    for (int i = 0; i < ids.size(); ++i) {
        if (ids[i] == projectId) {
            ids.erase(ids.begin() + i);
            startTimes.erase(startTimes.begin() + i); // delete the corresponding start time
            endTimes.erase(endTimes.begin() + i); // delete the corresponding end time
            this->numberofProjectsAssigned--;
            break;
        }
    }
}
