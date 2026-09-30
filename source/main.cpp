#include <iostream>
#include "Aircraft.h"
#include "Project.h"
#include "ScratchProject.h"
#include "ReconProject.h"
#include "AttackProject.h"
using std::cout;
using std::endl;
using std::cin;

#define EXIT 9

int runMenu();
void addAircraft();

//global variables
vector<Aircraft> availableAircrafts;
vector<ScratchProject> scratchProjects;
vector<ReconProject> reconProjects;	
vector<AttackProject> attackProjects;

int main() {
	
	int option = 0;
	do {
    option = runMenu();
    switch(option) {
        case 1: {
            addAircraft();
            break;
        }

        
        case EXIT:
            cout << "Exiting program..." << endl;
            break;
		//test case
		case 10: {
			for (const auto& aircraft : availableAircrafts) {
				cout << "Aircraft ID: " << aircraft.getId() << endl;
			}
			break;
		}
		//test case
		case 11: {
			for (const auto& project : scratchProjects) {	
				cout << "Scratch Project Name: " << project.getName() << endl << endl;
			}

        default:
            cout << "Invalid option. Please try again." << endl << endl;
            break;
		}
    }
} while(option != 9);
	return 0;
}



int runMenu() {
	int option = 0;
	cout << "Welcome to the Air Force Project Management System!" << endl << "Show options menu - 1" << endl << "EXIT - any other key" << endl;
		cin >> option;
	
	if(option != 1) {
		return EXIT;
	}
	cout << "Menu options:" << endl;
	cout << "Please select an option:" << endl << "1. Add an aircraft" << endl << "2. Add a scratch project" << endl << "3. Create an attack or reconnaissance project" << endl << "4. Auto assign aircraft to project" << endl << "5. Get all project within a time range" << endl << "6. Get all aircraft assigned to a project" << endl << "7. Check either a project is ready" << endl << "8. Get all unready projects in X hours ahead" << endl << "9. Exit" << endl;
	cin >> option;
	return option;
}

// Function to add an aircraft by id, connected to the main menu option 1.
void addAircraft() {
	int id;
	cout << "Enter the aircraft ID: ";
	cin >> id;
	Aircraft newAircraft(id);
	availableAircrafts.push_back(newAircraft);
	cout << "Aircraft with ID " << id << " added." << endl << endl;
}

void addScratchProject() {
	string name, desc, camera, flightCourse;
	int numOfAircraft;

	cout << "Enter project name: ";
	cin >> name;
	cout << "Enter project description: ";
	cin >> desc;
	cout << "Enter number of aircrafts needed: ";
	cin >> numOfAircraft;
	cout << "Enter camera type: ";
	cin >> camera;
	cout << "Enter flight course: ";
	cin >> flightCourse;

	ScratchProject newProject(name, desc, numOfAircraft, camera, flightCourse);
	scratchProjects.push_back(newProject);
	cout << "Scratch project added." << endl << endl;
}


