#include <iostream>
#include <vector>
#include <string>
#include "Aircraft.h"
#include "Project.h"
#include "ScratchProject.h"
#include "ReconProject.h"
#include "AttackProject.h"

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::string;

#define EXIT 9
#define RECON_PROJECT 1
#define ATTACK_PROJECT 2

int runMenu();
void addAircraft();
void addScratchProject();
void createProject();
void createReconProject(char basedOnScratch);
void printAllScratchProjects();
void printAllReconProjects();

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
                addAircraft();
                break;
            }
            case 2: {
                addScratchProject();
                break;
            }
            case 3: {
                createProject();
                break; // 1. Fixed missing break
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
                break; // 2. Fixed missing brace & break
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

    cout << "\nMenu options:" << endl;
    cout << "1. Add an aircraft" << endl 
         << "2. Add a scratch project" << endl 
         << "3. Create an attack or reconnaissance project" << endl 
         << "4. Auto assign aircraft to project" << endl 
         << "5. Get all project within a time range" << endl 
         << "6. Get all aircraft assigned to a project" << endl 
         << "7. Check either a project is ready" << endl 
         << "8. Get all unready projects in X hours ahead" << endl 
         << "9. Exit" << endl;
    cin >> option;
    return option;
}

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
        // Implement Attack Project creation here
    }
}

void createReconProject(char basedOnScratch) {
    string name, desc, camera, flightCourse, startTime, endTime;
    int numOfAircraft;
    int scratchProjectIndex;
    vector<Aircraft> aircraftList;

    if (basedOnScratch == 'y') {
        if (scratchProjects.empty()) {
            cout << "No scratch projects available to select from!" << endl << endl;
            return;
        }

        printAllScratchProjects();
        int maxIndex = static_cast<int>(scratchProjects.size());

        do {
            cout << "Enter the index of the scratch project to use: ";
            cin >> scratchProjectIndex;
            if (scratchProjectIndex < 1 || scratchProjectIndex > maxIndex) {
                cout << "Invalid index. Please try again." << endl;
            }
        } while (scratchProjectIndex < 1 || scratchProjectIndex > maxIndex);

        ScratchProject selectedScratchProject = scratchProjects[scratchProjectIndex - 1];

        cout << "Enter flight course: ";
        cin >> flightCourse;
        cout << "Enter start time: ";
        cin >> startTime;
        cout << "Enter end time: ";
        cin >> endTime;

        ReconProject newProject(selectedScratchProject, startTime, endTime, aircraftList);
        reconProjects.push_back(newProject);
        cout << newProject.getName() << " Reconnaissance project added." << endl << endl;
    } else {
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
        cout << "Enter start time: ";
        cin >> startTime;
        cout << "Enter end time: ";
        cin >> endTime;

        ReconProject newProject(name, desc, numOfAircraft, camera, flightCourse, startTime, endTime, aircraftList);
        reconProjects.push_back(newProject);
        cout << newProject.getName() << " Reconnaissance project added." << endl << endl;
    }
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
    int i = 1;
    cout << endl << "Reconnaissance Projects:" << endl << endl;
    for (const auto& project : reconProjects) {
        cout << i << ". Name: " << project.getName() << endl;
        i++;
    }
    cout << endl;
}