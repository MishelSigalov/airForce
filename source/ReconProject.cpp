#include "ReconProject.h"

ReconProject::ReconProject(string name, string desc, int numOfAircraft,
													 string camera, string flightCourse, string startTime, string endTime, vector<Aircraft> aircraftList)
		: ScratchProject(name, desc, numOfAircraft, camera, flightCourse),
			startTime(startTime), endTime(endTime), aircraftList(aircraftList)
{
}

ReconProject::ReconProject(ScratchProject scratchProject, string startTime, string endTime, vector<Aircraft> aircraftList)
    : ScratchProject(scratchProject.getName(), scratchProject.getDesc(), scratchProject.getNumOfAircraft(), scratchProject.getCamera(), scratchProject.getFlightCourse()),
      startTime(startTime), endTime(endTime), aircraftList(aircraftList)
{
}

void ReconProject::setAircraftList(vector<Aircraft> aircraftList) {
	this->aircraftList = aircraftList;
}

void ReconProject::addAircraft(Aircraft aircraft) {
	this->aircraftList.push_back(aircraft);
}