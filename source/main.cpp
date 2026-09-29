#include <iostream>
#include "Aircraft.h"
#include "Project.h"
#include "ScratchProject.h"
#include "ReconProject.h"
#include "AttackProject.h"
using std::cout;
using std::endl;

int main() {
	vector<Aircraft> aircraftList;
	Aircraft wow(3);
	aircraftList.push_back(wow);
	Aircraft wow2(15);
	aircraftList.push_back(wow2);
	
	ReconProject recon("Recon Project", "This is a recon project", 1923, "Camera1", "FlightCourse1", "2023-01-01 10:00:00", "2023-01-01 12:00:00", aircraftList);
	cout << "look: " << recon.getNumOfAircraft() << endl;

	Project pro("Project", "This is a project", 2);
	cout << "Number of Aircraft: " << pro.getNumOfAircraft() << endl;
	return 0;
}
