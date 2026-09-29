#pragma once
#include <string>
using std::string;

class Project {  
    public:
        Project(string name, string desc, int numOfAircraft);
        int getNumOfAircraft() const;
    protected:
        string name;
        string desc;
        int numOfAircraft; 

};