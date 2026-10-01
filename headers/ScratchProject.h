#pragma once
#include "Project.h"
#include <string>
using std::string;

class ScratchProject : public Project{  
    public:
        ScratchProject(string name, string desc, int numOfAircraft,
                       string camera, string flightCourse);
        string getCamera() const;
        string getFlightCourse() const;
        
        bool isReady() const override {
            // Scratch projects are not considered "ready" as they are templates for other projects
            return false;
        }
    protected:
        string camera;
        string flightCourse;

};