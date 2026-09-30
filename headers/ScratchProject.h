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
        
    protected:
        string camera;
        string flightCourse;

};