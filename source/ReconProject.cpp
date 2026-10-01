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

bool ReconProject::isReady() const {
	//considered ready if 80% of aircraft are assigned and the prep time is met
    // Round up 80% of required aircraft (e.g., 80% of 5 is 4, 80% of 3 is 2.4 -> 3)
    int requiredAircraft = static_cast<int>(std::ceil(this->numOfAircraft * 0.8));
	bool isEnoughAircraft = this->aircraftList.size() >= requiredAircraft; // Check if enough aircraft are assigned
	bool isEnoughPrepTime = TimeUtils::hasEnoughPrepTime(PREP_TIME_HOURS_RECON, this->startTime); // Check for the required prep time
	
	return isEnoughAircraft && isEnoughPrepTime;
}