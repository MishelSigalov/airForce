#include "ScratchProject.h"

ScratchProject::ScratchProject(string name, string desc, int numOfAircraft,
															 string camera, string flightCourse)
		: Project(name, desc, numOfAircraft),
			camera(camera), flightCourse(flightCourse)
{
}
