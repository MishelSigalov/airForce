#pragma once
#include <string>
using std::string;

class Project {  
    public:
        Project(string name, string desc, int numOfAircraft);
        int getNumOfAircraft() const;
        string getName() const;
        string getDesc() const;
        virtual bool isReady() const = 0; // Pure virtual function to be implemented by derived classes
        
    protected:
        string name;
        string desc;
        int numOfAircraft; 

};