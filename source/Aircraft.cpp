#include "Aircraft.h"

Aircraft::Aircraft(int id) : id(id)
{
}

int Aircraft::getId() const
{
    return id;
}