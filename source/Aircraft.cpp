#include "Aircraft.h"

Aircraft::Aircraft(int id) : id(id)
{
    this->status = true; // Set the initial status to available
}

int Aircraft::getId() const
{
    return id;
}

void Aircraft::enable(string startTime, string endTime) {
    this->status = true;
    this->startTime = startTime;
    this->endTime = endTime;
}
{
    this->status = true;
}

void Aircraft::disable()
{
    this->status = false;
    this->startTime = "";
    this->endTime = "";

}

bool Aircraft::isAvailable() const
{
    return this->status;
}
