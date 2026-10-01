#include "Aircraft.h"


Aircraft::Aircraft(int id) : id(id)
{
    this->numberofProjectsAssigned = 0; // Set the initial number of projects assigned to 0
}

int Aircraft::getId() const
{
    return id;
}

bool Aircraft::isAvailable(string startTime, string endTime) const {
    int bookedStart = 0;
    int bookedEnd = 0;

    //-60 and +60 are used due to maintace time between projects
    int requestedStart = timeToMinutes(startTime) - 60; 
    int requestedEnd = timeToMinutes(endTime) + 60; 

    for (int i = 0; i < startTimes.size(); i++) {
        bookedStart = timeToMinutes(startTimes[i]);
        bookedEnd = timeToMinutes(endTimes[i]);
        if (requestedStart < bookedEnd && bookedStart < requestedEnd) {
            return false;
        }
    }
    return true;
}

void Aircraft::assign(string startTime, string endTime, string projectName) {
    this->numberofProjectsAssigned++;
    this->projectNames.push_back(projectName);
    this->startTimes.push_back(startTime);
    this->endTimes.push_back(endTime);
}

void Aircraft::unassign(string projectName) {
    for (int i = 0; i < projectNames.size(); ++i) {
        if (projectNames[i] == projectName) {
            projectNames.erase(projectNames.begin() + i);
            startTimes.erase(startTimes.begin() + i); // delete the corresponding start time
            endTimes.erase(endTimes.begin() + i); // delete the corresponding end time
            this->numberofProjectsAssigned--;
            break;
        }
    }
}

int Aircraft::timeToMinutes(string time) const {
    int hour = std::stoi(time.substr(HOUR_START_INDEX, 2)); // 2-digit hour
    int minute = std::stoi(time.substr(MINUTE_START_INDEX, 2)); // 2-digit minute
    return hour * 60 + minute;
}
