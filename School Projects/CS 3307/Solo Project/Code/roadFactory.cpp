#include "roadFactory.h"

// createRoad method that will create road objects
std::unique_ptr<Road> roadFactory::createRoad(roadType type, const std::string& name, const std::string& desc, const std::string& traffic, int delay, int popHour, bool construction, int roadID) {
    // Checks which type of road is passed into the method
    switch(type) {
    // If the type is Local, then create a Local Road object
    case roadType::Local:
        return std::make_unique<Local>(name, desc, traffic, delay, popHour, construction, roadID);
    // If the type is Highway, then create a Highway Road object
    case roadType::Highway:
        return std::make_unique<Highway>(name, desc, traffic, delay, popHour, construction, roadID);
    // If the type was not one of the constant ones, then return null
    default:
        return nullptr;
    }
}
