#include "AttackProject.h"

AttackProject::AttackProject(string name, string desc, int numOfAircraft,
                                                         string weaponry, string coordinates, string startTime, string endTime, vector<Aircraft> aircraftList)
        : Project(name, desc, numOfAircraft),
            weaponry(weaponry), coordinates(coordinates), startTime(startTime), endTime(endTime), aircraftList(aircraftList)
{
}