#include "AttackProject.h"

int AttackProject::nextId = 2000;

// 1. Primary Field Constructor
AttackProject::AttackProject(const string& name, 
                           const string& desc, 
                           int numOfAircraft,
                           const string& weaponry, 
                           const string& coordinates, 
                           const string& startTime, 
                           const string& endTime, 
                           const vector<Aircraft*>& aircraftList)
    : Project(name, desc, numOfAircraft),
      id(++nextId), 
      weaponry(weaponry),
      coordinates(coordinates),
      startTime(startTime), 
      endTime(endTime), 
      aircraftList(aircraftList) 
{}

// 2. Delegate Constructor (Delegates to Primary Constructor)
AttackProject::AttackProject(const ScratchProject& scratchProject, 
                           const string& weaponry, 
                           const string& coordinates, 
                           const string& startTime, 
                           const string& endTime, 
                           const vector<Aircraft*>& aircraftList)
    : AttackProject(scratchProject.getName(), 
                    scratchProject.getDesc(), 
                    scratchProject.getNumOfAircraft(),
                    weaponry, 
                    coordinates, 
                    startTime, 
                    endTime, 
                    aircraftList) 
{}

void AttackProject::setAircraftList(vector<Aircraft*> aircraftList) {
    this->aircraftList = aircraftList;
}

void AttackProject::addAircraft(Aircraft* aircraft) {
    this->aircraftList.push_back(aircraft); 
}

void AttackProject::setStartTime(string newStartTime) {
  this->startTime = newStartTime;
}

void AttackProject::setEndTime(string newEndTime) {
  this->endTime = newEndTime;
}

string AttackProject::getStartTime() const {
  return this->startTime;
}

string AttackProject::getEndTime() const {
  return this->endTime;
}

const vector<Aircraft*>& AttackProject::getAircraftList() const {
  return this->aircraftList;
}

int AttackProject::getId() const {
  return this->id;
}

bool AttackProject::isReady() const {
  //Considered ready if all aircraft are assigned and the prep time is met
	bool isEnoughAircraft = this->aircraftList.size() == this->numOfAircraft; // Check if enough aircraft are assigned
	bool isEnoughPrepTime = TimeUtils::hasEnoughPrepTime(PREP_TIME_HOURS_ATTACK, this->startTime); // Check for the required prep time
	
	return isEnoughAircraft && isEnoughPrepTime;
}