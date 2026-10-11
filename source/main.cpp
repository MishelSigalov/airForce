#include <iostream>
#include <vector>
#include <string>
#include "Aircraft.h"
#include "Project.h"
#include "ScratchProject.h"
#include "ReconProject.h"
#include "AttackProject.h"
#include "TimeUtils.h"

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::string;
using std::to_string;

#define EXIT 9
#define RECON_PROJECT 1
#define ATTACK_PROJECT 2

// Function declarations
int runMenu();
void addAircraft();
void addScratchProject();
void createProject();
void createReconProject(char basedOnScratch);
void createAttackProject(char basedOnScratch);
void autoAssignAircraftToProject(string projectSelection);
void printAllProjectsInTimeRange(string startTime, string endTime);
void changeTimes(string projectSelection, string newStartTime, string newEndTime);
void isOperationReady(string projectSelection);
void printAllUnreadyProjectsInXHours(int hoursAhead);

string getSelectedProject();
void printAllAircrafts();
void printAllScratchProjects();
void printAllReconProjects();
void printAllAttackProjects();
void printAllAircraftsInProject(int projectId, char projectType);

// Global variables
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
				// Add an aircraft
                addAircraft();
                break;
            }

            case 2: {
				// Add a scratch project
                addScratchProject();
                break;
            }

            case 3: {
				// Create an attack or reconnaissance project
                createProject();
                break; 
            }

			case 4: {
				if(availableAircrafts.empty()) {
					cout << "No available aircrafts to assign!" << endl << endl;
					break;
				}
				// Auto assign aircraft to project
                autoAssignAircraftToProject(getSelectedProject());
				break;
			}

			case 5: {
				cout << "---------Get all projects within a time range---------" << endl;
				string startTime = TimeUtils::getTime('s');
				string endTime = TimeUtils::getTime('e');
				printAllProjectsInTimeRange(startTime, endTime);

				break;
			}

			case 6:{
				cout << "---------Change project times---------" << endl;
				string projectSelection = getSelectedProject();
				string newStartTime = TimeUtils::getTime('s');
				string newEndTime = TimeUtils::getTime('e');
				changeTimes(projectSelection, newStartTime, newEndTime);
				break;
			}

			case 7: {
				cout << "---------Check if a project is ready---------" << endl;
				string projectSelection = getSelectedProject();
				isOperationReady(projectSelection);
				break;
			}

			case 8 : {
				cout << "---------Get all unready projects in X hours ahead---------" << endl;
				int hoursAhead = 0;
				cout << "Enter the number of hours ahead to check for unready projects: ";
				cin >> hoursAhead;
				printAllUnreadyProjectsInXHours(hoursAhead);
				break;
			}

            case EXIT:
                cout << "Exiting program..." << endl;
                break;

            // Test cases
            case 10: {
                for (const auto& aircraft : availableAircrafts) {
                    cout << "Aircraft ID: " << aircraft.getId() << endl;
                }
                break;
            }
            case 11: {
                printAllScratchProjects();
                break;
            }
            case 12: {
                printAllReconProjects();
                break;
            }
            default:
                cout << "Invalid option. Please try again." << endl << endl;
                break;
        }
    } while(option != EXIT);

    return 0;
}

int runMenu() {
    int option = 0;
    cout << "Welcome to the Air Force Project Management System!" << endl 
         << "Show options menu - 1" << endl 
         << "EXIT - any other key" << endl;
    cin >> option;
    
    if (option != 1) {
        return EXIT;
    }

    cout << endl << "Menu options:" << endl;
    cout << "1. Add an aircraft" << endl 
         << "2. Add a scratch project" << endl 
         << "3. Create an attack or reconnaissance project" << endl 
         << "4. Auto assign aircraft to project" << endl 
         << "5. Get all project within a time range" << endl 
         << "6. Change project times" << endl 
         << "7. Check either a project is ready" << endl 
         << "8. Get all unready projects in X hours ahead" << endl 
         << "9. Exit" << endl;
    cin >> option;
    return option;
}

// Function to add an aircraft by id. (1)
void addAircraft() {
    int id = 0;
    cout << "Enter the aircraft ID: ";
    cin >> id;
    Aircraft newAircraft(id);
    availableAircrafts.push_back(newAircraft);
    cout << "Aircraft with ID " << id << " added." << endl << endl;
}

// Function to add a scratch project. (2)
void addScratchProject() {
    string name, desc, camera, flightCourse;
    int numOfAircraft = 0;

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

// Functions to create a project (either Reconnaissance or Attack). (3)
void createProject() {
    int projectType = 0;
    char basedOnScratch;
    cout << "Select project type to create:" << endl;
    do {
        cout << "1. Reconnaissance Project" << endl;
        cout << "2. Attack Project" << endl;
        cin >> projectType;
        if (projectType != RECON_PROJECT && projectType != ATTACK_PROJECT) {
            cout << "Invalid option. Please try again." << endl;
        }
    } while (projectType != RECON_PROJECT && projectType != ATTACK_PROJECT);

    cout << "Do you want to create the project based on an existing scratch project? (y/n): ";
    do {
        cin >> basedOnScratch;
        if (basedOnScratch != 'y' && basedOnScratch != 'n') {
            cout << "Invalid option. Please try again. (y/n)" << endl;
        }
    } while (basedOnScratch != 'y' && basedOnScratch != 'n');
    
    if (projectType == RECON_PROJECT) {
        createReconProject(basedOnScratch);
    } else if (projectType == ATTACK_PROJECT) {
        createAttackProject(basedOnScratch);
    }
}

//create a Reconnaissance project, either based on a scratch project or from scratch (3)
void createReconProject(char basedOnScratch) {
    string name, desc, camera, flightCourse, startTime, endTime;
    int numOfAircraft = 0;
    int scratchProjectIndex = 0;
	int maxIndex = 0;
    vector<Aircraft*> aircraftList;

    if (basedOnScratch == 'y') {
        if (scratchProjects.empty()) {
            cout << "No scratch projects available to select from!" << endl << endl;
            return;
        }

        printAllScratchProjects();
        maxIndex = scratchProjects.size();

        do {
            cout << "Enter the index of the scratch project to use: ";
            cin >> scratchProjectIndex;
            if (scratchProjectIndex < 1 || scratchProjectIndex > maxIndex) {
                cout << "Invalid index. Please try again." << endl;
            }
        } while (scratchProjectIndex < 1 || scratchProjectIndex > maxIndex);

		//-1 because the user sees a 1-based index, but the vector is 0-based
        ScratchProject selectedScratchProject = scratchProjects[scratchProjectIndex - 1];

		startTime = TimeUtils::getTime('s');
		endTime = TimeUtils::getTime('e');

        ReconProject newProject(selectedScratchProject, startTime, endTime, aircraftList);
        reconProjects.push_back(newProject);
        cout << newProject.getName() << " Reconnaissance project added." << " ID: " << newProject.getId() << endl << endl;
    } 
	else {
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
		startTime = TimeUtils::getTime('s');
		endTime = TimeUtils::getTime('e');

        ReconProject newProject(name, desc, numOfAircraft, camera, flightCourse, startTime, endTime, aircraftList);
        reconProjects.push_back(newProject);
        cout << newProject.getName() << " Reconnaissance project added." << " ID: " << newProject.getId() << endl << endl;
    }
}

//create an Attack project, either based on a scratch project or from scratch (3)
void createAttackProject(char basedOnScratch) {
	string name, desc, weaponry, coordinates, startTime, endTime;
	int numOfAircraft = 0;
	int scratchProjectIndex = 0;
	int maxIndex = 0;
	vector<Aircraft*> aircraftList;

	if (basedOnScratch == 'y') {
		if (scratchProjects.empty()) {
			cout << "No scratch projects available to select from!" << endl << endl;
			return;
		}

		printAllScratchProjects();
		maxIndex = scratchProjects.size();

		do {
			cout << "Enter the index of the scratch project to use: ";
			cin >> scratchProjectIndex;
			if (scratchProjectIndex < 1 || scratchProjectIndex > maxIndex) {
				cout << "Invalid index. Please try again." << endl;
			}
		} while (scratchProjectIndex < 1 || scratchProjectIndex > maxIndex);

		ScratchProject selectedScratchProject = scratchProjects[scratchProjectIndex - 1];

		cout << "Enter weaponry: ";
		cin >> weaponry;
		cout << "Enter coordinates: ";
		cin >> coordinates;
		startTime = TimeUtils::getTime('s');
		endTime = TimeUtils::getTime('e');

		AttackProject newProject(selectedScratchProject, weaponry, coordinates, startTime, endTime, aircraftList);
		attackProjects.push_back(newProject);
		cout << newProject.getName() << " Attack project added." << " ID: " << newProject.getId() << endl << endl;
	} 
	else {
		cout << "Enter project name: ";
		cin >> name;
		cout << "Enter project description: ";
		cin >> desc;
		cout << "Enter number of aircrafts needed: ";
		cin >> numOfAircraft;
		cout << "Enter weaponry: ";
		cin >> weaponry;
		cout << "Enter coordinates: ";
		cin >> coordinates;
		startTime = TimeUtils::getTime('s');
		endTime = TimeUtils::getTime('e');

		AttackProject newProject(name, desc, numOfAircraft, weaponry, coordinates, startTime, endTime, aircraftList);
		attackProjects.push_back(newProject);
		cout << newProject.getName() << " Attack project added."  << " ID: " << newProject.getId() << endl << endl;
	}
}



// This function will auto assign available aircraft to projects based on their availability. (4)
void autoAssignAircraftToProject(string projectSelection) {
    if (projectSelection.empty() || projectSelection == "error") {
        return;
    }

    char projectType = projectSelection[0]; // either r for Reconnaissance or a for Attack
    int selectedProjectIndex = std::stoi(projectSelection.substr(1));

    int projectId = 0;
	string projectName = "";
    int requiredAircraft = 0; // number of aircraft required for the project
	int assignedCount = 0; // keeps track of how many aircraft are assigned in this run of the function
	int assignedAircraft = 0; // number of aircraft already assigned to the project
	int alreadyAssignedCount = 0;
    string startTime = "";
    string endTime = "";

	if(projectType == 'r') {
		ReconProject& selectedProject = reconProjects[selectedProjectIndex];
		projectId = selectedProject.getId();
		projectName = selectedProject.getName();
		requiredAircraft = selectedProject.getNumOfAircraft();
		alreadyAssignedCount = selectedProject.getAircraftList().size();
		
		startTime = selectedProject.getStartTime();
		endTime = selectedProject.getEndTime();
	} 
	else if(projectType == 'a') {
		
		AttackProject& selectedProject = attackProjects[selectedProjectIndex];
		projectId = selectedProject.getId();
		projectName = selectedProject.getName();
		requiredAircraft = selectedProject.getNumOfAircraft();
		alreadyAssignedCount = selectedProject.getAircraftList().size();

		startTime = selectedProject.getStartTime();
		endTime = selectedProject.getEndTime();
	}

	if(requiredAircraft == alreadyAssignedCount) {
		cout << "All required aircrafts are already assigned to the project." << endl;
		return;
	}


	for (auto& aircraft : availableAircrafts) {
        if (!aircraft.isAvailable(startTime, endTime)) {
            continue;
        }
		assignedCount++;
		aircraft.assign(startTime, endTime, projectId);
		if(projectType == 'r') {
			reconProjects[selectedProjectIndex].addAircraft(&aircraft);
		} 
		else if(projectType == 'a') {
			attackProjects[selectedProjectIndex].addAircraft(&aircraft);
		}


		if (assignedCount == requiredAircraft) {
			cout << endl << endl << "All " << requiredAircraft << " required aircrafts assigned to the project." << endl;
			break;
		}
	}

	if (assignedCount < requiredAircraft) {
		cout << endl << endl << "Only " << assignedCount << " out of " << requiredAircraft << " required aircrafts assigned to the project." << endl;
	} 
	
	printAllAircraftsInProject(projectId, projectType);
    
}


// Function to print all projects within a specified time range. (5)
void printAllProjectsInTimeRange(string startTime, string endTime) {
    int rangeStartMin = TimeUtils::timeToMinutes(startTime);
    int rangeEndMin   = TimeUtils::timeToMinutes(endTime);

    if (rangeEndMin <= rangeStartMin) {
        cout << "Error: End time must occur after start time.\n";
        return;
    }

    cout << endl << "========================================"<< endl;
    cout << " Projects with Start or End in Range: " 
         << startTime << "  -->  " << endTime << "" << endl;
    cout << "========================================" << endl;

    bool foundAny = false;

    // Check Reconnaissance Projects
    for (auto& project : reconProjects) {
        int projStartMin = TimeUtils::timeToMinutes(project.getStartTime());
        int projEndMin   = TimeUtils::timeToMinutes(project.getEndTime());

        bool startInRange = (projStartMin >= rangeStartMin && projStartMin <= rangeEndMin);
        bool endInRange   = (projEndMin >= rangeStartMin && projEndMin <= rangeEndMin);

		// If either the start or end time of the project falls within the specified range, it is considered a match.
        if (startInRange || endInRange) {
            cout << "[Recon Project] ID: " << project.getId() 
                 << " | Name: " << project.getName()
                 << " | Time: " << project.getStartTime() << " to " << project.getEndTime() 
                 << endl;
            foundAny = true;
        }
    }

    // Check Attack Projects
    for (auto& project : attackProjects) {
        int projStartMin = TimeUtils::timeToMinutes(project.getStartTime());
        int projEndMin   = TimeUtils::timeToMinutes(project.getEndTime());

        bool startInRange = (projStartMin >= rangeStartMin && projStartMin <= rangeEndMin);
        bool endInRange   = (projEndMin >= rangeStartMin && projEndMin <= rangeEndMin);

		// If either the start or end time of the project falls within the specified range, it is considered a match.
        if (startInRange || endInRange) {
            cout << "[Attack Project] ID: " << project.getId() 
                 << " | Name: " << project.getName()
                 << " | Time: " << project.getStartTime() << " to " << project.getEndTime() 
                 << endl;
            foundAny = true;
        }
    }

    if (!foundAny) {
        cout << "No projects found within the specified time range.\n";
    }

	cout << "========================================" << endl << endl;
}

// Function to change the start and end times of a project, while checking for aircraft availability. (6)
void changeTimes(string projectSelection, string newStartTime, string newEndTime) {
    int newStartMin = TimeUtils::timeToMinutes(newStartTime);
    int newEndMin   = TimeUtils::timeToMinutes(newEndTime);

    // 1. Validate chronological order of new range
    if (newEndMin <= newStartMin) {
        cout << "Error: New end time must occur after new start time. Operation canceled.\n";
        return;
    }

    vector<Aircraft*> conflictingAircraft;
    vector<Aircraft*> validAircraft;
    char projectType = projectSelection[0]; // 'r' or 'a'
    int selectedProjectIndex = std::stoi(projectSelection.substr(1));

    int projectId = 0;
    char choice;
    string projectName = "";
    vector<Aircraft*> assignedAircraft;
    string oldStartTime = "";
    string oldEndTime = "";

    // Retrieve active project reference and member data
    if (projectType == 'r') {
        ReconProject& selectedProject = reconProjects[selectedProjectIndex];
        projectId = selectedProject.getId();
        projectName = selectedProject.getName();

        assignedAircraft = selectedProject.getAircraftList();
        oldStartTime = selectedProject.getStartTime();
        oldEndTime = selectedProject.getEndTime();
    } 
    else if (projectType == 'a') {
        AttackProject& selectedProject = attackProjects[selectedProjectIndex];
        projectId = selectedProject.getId();
        projectName = selectedProject.getName();

        assignedAircraft = selectedProject.getAircraftList();
        oldStartTime = selectedProject.getStartTime();
        oldEndTime = selectedProject.getEndTime();
    }

    // 2. Check each aircraft pointer in the project for availability in the new window
    for (Aircraft* aircraft : assignedAircraft) {
        if (aircraft->isAvailable(newStartTime, newEndTime, projectId)) {
            validAircraft.push_back(aircraft);
        } else {
            conflictingAircraft.push_back(aircraft);
        }
    }

    // 3. If there are conflicting aircraft, warn user and display which will be unassigned
    if (!conflictingAircraft.empty()) {
        cout << "\n--------------------------------------------------\n";
        cout << " WARNING: Time change causes schedule conflicts!\n";
        cout << " The following aircraft will be UNASSIGNED from this project:\n";
        cout << "--------------------------------------------------\n";

        for (const Aircraft* aircraft : conflictingAircraft) {
            cout << " - Aircraft ID: " << aircraft->getId() << endl;
        }

        while (true) {
            cout << "\nAre you sure you want to proceed with this change? (y/n): ";
            
            if (cin >> choice) {
                choice = std::tolower(choice);
                if (choice == 'y' || choice == 'n') {
                    break;
                }
            }

            cout << "Invalid response! Please enter 'y' for yes or 'n' for no.\n";
        }

        // Abort action if user cancels
        if (choice == 'n') {
            cout << "\nAction canceled. Project times remain unchanged:\n";
            cout << " Start: " << oldStartTime << " | End: " << oldEndTime << endl;
            return;
        }

        // 4. User confirmed: Unassign conflicting aircraft from master availableAircrafts vector
        for (const Aircraft* conflicting : conflictingAircraft) {
            for (Aircraft& globalAircraft : availableAircrafts) {
                if (globalAircraft.getId() == conflicting->getId()) {
                    globalAircraft.unassign(projectId); // Modifies central master object
                    break;
                }
            }
        }

        // Keep only remaining valid aircraft pointers in the project
        if (projectType == 'r') {
            reconProjects[selectedProjectIndex].setAircraftList(validAircraft);
        } else if (projectType == 'a') {
            attackProjects[selectedProjectIndex].setAircraftList(validAircraft);
        }
    }

    // 5. Update project timestamps
    if (projectType == 'r') {
        reconProjects[selectedProjectIndex].setStartTime(newStartTime);
        reconProjects[selectedProjectIndex].setEndTime(newEndTime);
    }   
    else if (projectType == 'a') {
        attackProjects[selectedProjectIndex].setStartTime(newStartTime);
        attackProjects[selectedProjectIndex].setEndTime(newEndTime);
    }

    cout << "\nProject times updated successfully!\n";
    cout << " Previous: " << oldStartTime << " to " << oldEndTime << endl;
    cout << " Updated:  " << newStartTime << " to " << newEndTime << "\n\n\n";
    
    if (!conflictingAircraft.empty()) {
        cout << " Note: " << conflictingAircraft.size() << " conflicting aircraft unassigned.\n";
    }
}

// Function to check if a project is ready for operation. (7)
void isOperationReady(string projectSelection) {
	if (projectSelection.empty() || projectSelection == "error") {
		return;
	}

	char projectType = projectSelection[0]; // either r for Reconnaissance or a for Attack
	int selectedProjectIndex = std::stoi(projectSelection.substr(1));

	if(projectType == 'r') {
		ReconProject& selectedProject = reconProjects[selectedProjectIndex];
		if(selectedProject.isReady()) {
			cout << "Reconnaissance Project " << selectedProject.getName() << " is ready for operation." << endl << endl;
		} else {
			cout << "Reconnaissance Project " << selectedProject.getName() << " is NOT ready for operation." << endl << endl;
		}
	} 
	else if(projectType == 'a') {
		AttackProject& selectedProject = attackProjects[selectedProjectIndex];
		if(selectedProject.isReady()) {
			cout << "Attack Project " << selectedProject.getName() << " is ready for operation." << endl << endl;
		} else {
			cout << "Attack Project " << selectedProject.getName() << " is NOT ready for operation." << endl << endl;
		}
	}
}

// Function to print all unready projects within a specified number of hours ahead. (8)
void printAllUnreadyProjectsInXHours(int hoursAhead) {
	int currentMin = TimeUtils::getCurrentTimeInMinutes();
	int futureMin = TimeUtils::addHoursToTime(currentMin, hoursAhead);
	int projectStartMin = 0;
	bool foundUnready = false;

	cout << "Checking for unready projects between now and  the next" << hoursAhead << " hours..." << endl << endl;

	for (const auto& project : reconProjects) {
		if (!project.isReady()) {
			projectStartMin = TimeUtils::timeToMinutes(project.getStartTime());

			if (projectStartMin >= currentMin && projectStartMin <= futureMin) {
				cout << "[Recon Project] ID: " << project.getId() 
					 << " | Name: " << project.getName()
					 << " | Time: " << project.getStartTime() << " to " << project.getEndTime() 
					 << endl;
				foundUnready = true;
			}
		}
	}

	for (const auto& project : attackProjects) {
		if (!project.isReady()) {
			projectStartMin = TimeUtils::timeToMinutes(project.getStartTime());

			if (projectStartMin >= currentMin && projectStartMin <= futureMin) {
				cout << "[Attack Project] ID: " << project.getId() 
					 << " | Name: " << project.getName()
					 << " | Time: " << project.getStartTime() << " to " << project.getEndTime() 
					 << endl;
				foundUnready = true;
			}
		}
	}

	if (!foundUnready) {
		cout << "No unready projects found in the next " << hoursAhead << " hours.\n";
	}

	cout << endl << endl;
}





/* Helper functions */

// Function gathers information about the selected project
string getSelectedProject() {
	string selection = ""; //selection[0] = project type (r/a), selection[1] = project index
	char projectType;
	int selectedProjectIndex = 0;
	int maxIndex = 0;
	do{
		cout << "What project would you like to select, reconnaissance or attack? (r/a): ";
		cin >> projectType;
		if (projectType != 'r' && projectType != 'a') {
			cout << "Invalid option. Please try again. (r/a)" << endl;
		}
	} while (projectType != 'r' && projectType != 'a');

	selection += projectType;

	if(projectType == 'r') {
		maxIndex = reconProjects.size();
		if (maxIndex == 0) {
			cout << "No Reconnaissance projects available to select from!" << endl << endl;
            return "error";
		}

		printAllReconProjects();
		do {
			cout << "Enter the index of the Reconnaissance project to assign aircraft to: ";
			cin >> selectedProjectIndex;
			if (selectedProjectIndex < 1 || selectedProjectIndex > maxIndex) {
				cout << "Invalid index. Please try again." << endl;
			}
		} while (selectedProjectIndex < 1 || selectedProjectIndex > maxIndex);
		
	} 
	else if(projectType == 'a') {
		maxIndex = attackProjects.size();
		if (maxIndex == 0) {
			cout << "No Attack projects available to select from!" << endl << endl;
            return "error";
		}
		printAllAttackProjects();
		do {
			cout << "Enter the index of the Attack project to assign aircraft to: ";
			cin >> selectedProjectIndex;
			if (selectedProjectIndex < 1 || selectedProjectIndex > maxIndex) {
				cout << "Invalid index. Please try again." << endl;
			}
		} while (selectedProjectIndex < 1 || selectedProjectIndex > maxIndex);
	}

	//-1 because the user sees a 1-based index, but the vector is 0-based
	selection += std::to_string(selectedProjectIndex - 1); //append the selected project index to the selection string
	return selection;
}

void printAllAircrafts() {
	cout << endl << "Available Aircrafts:" << endl << endl;
	for (const auto& aircraft : availableAircrafts) {
		cout << "Aircraft ID: " << aircraft.getId() << endl;
	}
	cout << endl;
}

void printAllScratchProjects() {
    int i = 1;
    cout << endl << "Scratch Projects:" << endl << endl;
    for (const auto& project : scratchProjects) {
        cout << i << ". Name: " << project.getName() << endl;
        i++;
    }
    cout << endl;
}

void printAllReconProjects() {
	if(reconProjects.empty()) {
		cout << endl << "No Reconnaissance projects!" << endl << endl;
		return;
	}
    int i = 1;
    cout << endl << "Reconnaissance Projects:" << endl << endl;
    for (const auto& project : reconProjects) {
        cout << i << ". Name: " << project.getName() << ", ID: " << project.getId() << endl;
        i++;
    }
    cout << endl;
}

void printAllAttackProjects() {
	if(attackProjects.empty()) {
		cout << endl << "No Attack projects!" << endl << endl;
		return;
	}
	int i = 1;
	cout << endl << "Attack Projects:" << endl << endl;
	for (const auto& project : attackProjects) {
		cout << i << ". Name: " << project.getName() << ", ID: " << project.getId() << endl;
		i++;
	}
	cout << endl;
}	

void printAllAircraftsInProject(int projectId, char projectType) {
	if(projectType == 'r') {
		for (const auto& project : reconProjects) {
			if (project.getId() == projectId) {
				cout << endl << "Total " << project.getAircraftList().size() << " Aircrafts in Reconnaissance Project " << project.getName() << ": " << endl;
				for (const auto& aircraft : project.getAircraftList()) {
					cout << "Aircraft ID: " << aircraft->getId() << endl;
				}
			}
		}
	} 
	else if (projectType == 'a') {
		for (const auto& project : attackProjects) {
			if (project.getId() == projectId) {
				cout << endl << "Total " << project.getAircraftList().size() << " Aircrafts in Attack Project " << project.getName() << ": " << endl << endl;
				for (const auto& aircraft : project.getAircraftList()) {
					cout << "Aircraft ID: " << aircraft->getId() << endl;
				}
			}
		}
	}
	cout << endl << endl;
}
