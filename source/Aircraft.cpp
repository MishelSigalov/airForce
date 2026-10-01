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
    // 60-minute maintenance window
    int requestedStart = timeToMinutes(startTime) - 60; 
    int requestedEnd   = timeToMinutes(endTime) + 60; 

    for (size_t i = 0; i < startTimes.size(); i++) {
        int bookedStart = timeToMinutes(startTimes[i]);
        int bookedEnd   = timeToMinutes(endTimes[i]);

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

int Aircraft::timeToMinutes(string time) const {
    std::tm tm = {};
    tm.tm_year = stoi(time.substr(YEAR_START_INDEX, 4)) - 1900; // Years since 1900
    tm.tm_mon  = stoi(time.substr(MONTH_START_INDEX, 2)) - 1;    // Months 0-11
    tm.tm_mday = stoi(time.substr(DAY_START_INDEX, 2));        // Day 1-31
    tm.tm_hour = stoi(time.substr(HOUR_START_INDEX, 2));       // Hour 0-23
    tm.tm_min  = stoi(time.substr(MINUTE_START_INDEX, 2));       // Minute 0-59

    std::time_t timeInSeconds = std::mktime(&tm); // this will give you the time in seconds since epoch
    return static_cast<int>(timeInSeconds / SECONDS_IN_A_MINUTE); // Convert seconds to minutes and then to int
}
