#include "AttackProject.h"

AttackProject::AttackProject(string name, string desc, int numOfAircraft,
                                                         string weaponry, string coordinates, string startTime, string endTime, vector<Aircraft> aircraftList)
        : Project(name, desc, numOfAircraft),
            weaponry(weaponry), coordinates(coordinates), startTime(startTime), endTime(endTime), aircraftList(aircraftList)
{
}

#include "AttackProject.h"

AttackProject::AttackProject(ScratchProject scratchProject, string weaponry, 
                             string coordinates, string startTime, 
                             string endTime, vector<Aircraft> aircraftList)
    : Project(scratchProject.getName(), scratchProject.getDesc(), scratchProject.getNumOfAircraft()),
      weaponry(weaponry),
      coordinates(coordinates),
      startTime(startTime),
      endTime(endTime),
      aircraftList(aircraftList)
{
}

void AttackProject::setAircraftList(vector<Aircraft> aircraftList) {
	this->aircraftList = aircraftList;
}

void AttackProject::addAircraft(Aircraft aircraft) {
	this->aircraftList.push_back(aircraft);
}

string AttackProject::getStartTime() const {
  return this->startTime;
}

string AttackProject::getEndTime() const {
  return this->endTime;
}

const vector<Aircraft>& AttackProject::getAircraftList() const {
  return this->aircraftList;
}