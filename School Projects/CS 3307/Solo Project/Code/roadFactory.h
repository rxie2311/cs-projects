#ifndef ROADFACTORY_H
#define ROADFACTORY_H

// C++ Libraries
#include <memory>
#include <string>

// Other Classes
#include "road.h"

// roadFactory class - For the Factory design pattern
class roadFactory {
public:
    // Constant variables for the two types of roads
    enum class roadType { Local, Highway };
    // createRoad method that creates a new Road object
    static std::unique_ptr<Road> createRoad(roadType type, const std::string& name, const std::string& desc, const std::string& traffic, int delay, int popHour, bool construction, int roadID);
};

#endif // ROADFACTORY_H
