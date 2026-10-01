#include "ReconProject.h"

int ReconProject::nextId = 1000;

ReconProject::ReconProject(const string& name, 
                         const string& desc, 
                         int numOfAircraft,
                         const string& camera, 
                         const string& flightCourse, 
                         const string& startTime, 
                         const string& endTime, 
                         const vector<Aircraft*>& aircraftList)
    : ScratchProject(name, desc, numOfAircraft, camera, flightCourse),
      id(++nextId), 
      startTime(startTime), 
      endTime(endTime), 
      aircraftList(aircraftList) 
{}

// 2. Delegate Constructor (Reuses the first constructor to prevent duplicate code)
ReconProject::ReconProject(const ScratchProject& scratchProject, 
                         const string& startTime, 
                         const string& endTime, 
                         const vector<Aircraft*>& aircraftList)
    : ReconProject(scratchProject.getName(), 
                   scratchProject.getDesc(), 
                   scratchProject.getNumOfAircraft(),
                   scratchProject.getCamera(), 
                   scratchProject.getFlightCourse(), 
                   startTime, 
                   endTime, 
                   aircraftList) 
{}

void ReconProject::setAircraftList(vector<Aircraft*> aircraftList) {
	this->aircraftList = aircraftList;
}

void ReconProject::addAircraft(Aircraft* aircraft) {
	this->aircraftList.push_back(aircraft);
}

void ReconProject::setStartTime(string newStartTime) {
	this->startTime = newStartTime;
}

void ReconProject::setEndTime(string newEndTime) {
	this->endTime = newEndTime;
}

string ReconProject::getStartTime() const {
	return this->startTime;
}

string ReconProject::getEndTime() const {
	return this->endTime;
}

const vector<Aircraft*>& ReconProject::getAircraftList() const {
	return this->aircraftList;
}

int ReconProject::getId() const {
	return this->id;
}