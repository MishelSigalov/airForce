#include "Project.h"

Project::Project(string name, string desc, int numOfAircraft)
	: name(name), desc(desc), numOfAircraft(numOfAircraft)
{
}

int Project::getNumOfAircraft() const {
    return this->numOfAircraft;
}