#include <iostream>
#include "Aircraft.h"
#include "Project.h"
#include "ScratchProject.h"
#include "ReconProject.h"
#include "AttackProject.h"
using std::cout;
using std::endl;
using std::cin;

int runMenu();
int addAircraft();

int main() {
	vector<Aircraft> availableAircrafts;
	int option = 0;
	do {
    option = runMenu();
    switch(option) {
        case 1: { // Added opening brace
            int id = addAircraft();
            Aircraft newAircraft(id);
            availableAircrafts.push_back(newAircraft);
            cout << "Aircraft with ID " << id << " added." << endl << endl;
            break;
        } // Added closing brace
        
        case 9:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid option. Please try again." << endl;
            break;
    }
} while(option != 9);
	return 0;
}



int runMenu() {
	int option = 0;
	cout << "Welcome to the Air Force Project Management System!" << endl;
	cout << "Please select an option:" << endl << "1. Add an aircraft" << endl << "2. Add a scratch project" << endl << "3. Create an attack or reconnaissance project" << endl << "4. Auto assign aircraft to project" << endl << "5. Get all project within a time range" << endl << "6. Get all aircraft assigned to a project" << endl << "7. Check either a project is ready" << endl << "8. Get all unready projects in X hours ahead" << endl << "9. Exit" << endl;
	cin >> option;
	return option;
}

int addAircraft() {
	int id;
	cout << "Enter the aircraft ID: ";
	cin >> id;
	return id;
}
