#pragma once

class Aircraft {  
    public:
        Aircraft(int id);
        int getId() const;
        bool isAvailable() const;
        void enable(string startTime, string endTime);
        void disable();
        
    private:
        int id;
        bool status;
        string startTime;
        string endTime;
};