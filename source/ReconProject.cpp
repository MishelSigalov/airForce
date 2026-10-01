#include "ReconProject.h"

int ReconProject::nextId = 0;

ReconProject::ReconProject(string name, string desc, int numOfAircraft,
													 string camera, string flightCourse, string startTime, string endTime, vector<Aircraft> aircraftList)
		: ScratchProject(name, desc, numOfAircraft, camera, flightCourse),
			id(++nextId), startTime(startTime), endTime(endTime), aircraftList(aircraftList)
{
}

ReconProject::ReconProject(ScratchProject scratchProject, string startTime, string endTime, vector<Aircraft> aircraftList)
    : ScratchProject(scratchProject.getName(), scratchProject.getDesc(), scratchProject.getNumOfAircraft(), scratchProject.getCamera(), scratchProject.getFlightCourse()),
      id(++nextId), startTime(startTime), endTime(endTime), aircraftList(aircraftList)
{
}

void ReconProject::setAircraftList(vector<Aircraft> aircraftList) {
	this->aircraftList = aircraftList;
}

void ReconProject::addAircraft(Aircraft aircraft) {
	this->aircraftList.push_back(aircraft);
}

string ReconProject::getStartTime() const {
	return this->startTime;
}

string ReconProject::getEndTime() const {
	return this->endTime;
}

const vector<Aircraft>& ReconProject::getAircraftList() const {
	return this->aircraftList;
}

int ReconProject::getId() const {
	return this->id;
}