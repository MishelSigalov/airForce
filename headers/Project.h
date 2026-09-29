#pragma once
#include <string>
using std::string;

class Project {  
    public:
        Project(string name, string desc, int numOfAircraft);
    protected:
        string name;
        string desc;
        int numOfAircraft; 

};