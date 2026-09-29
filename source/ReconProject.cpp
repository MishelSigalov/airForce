#include "ReconProject.h"

ReconProject::ReconProject(string name, string desc, int numOfAircraft,
													 string camera, string flightCourse, string startTime, string endTime, vector<Aircraft> aircraftList)
		: ScratchProject(name, desc, numOfAircraft, camera, flightCourse),
			startTime(startTime), endTime(endTime), aircraftList(aircraftList)
{
}