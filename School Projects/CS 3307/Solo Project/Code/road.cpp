#include "road.h"

// LOCAL CLASS
// Constructor
Local::Local(const std::string& name, const std::string& desc, const std::string& traffic, int delay, int popHour, bool construction, int roadID) :
    name(name), desc(desc), traffic(traffic), delay(delay), popHour(popHour), construction(construction), roadID(roadID) {}

// GET methods
// Returns the name of the road
std::string Local::getName() const {
    return name;
}

// Returns the description of the road
std::string Local::getDesc() const {
    return desc;
}

// Returns the traffic status of the road
std::string Local::getTraffic() const {
    return traffic;
}

// Returns "Local" since it is a local road
std::string Local::getType() const {
    return "Local";
}

// Returns the approx. delay in minutes of the road
int Local::getDelay() const {
    return delay;
}

// Returns the most popular hour (in 24 hour time) of the road
int Local::getPopHour() const {
    return popHour;
}

// Returns True or False depending on if there is construction on the road
bool Local::getConstruction() const {
    return construction;
}

// Returns the unique road ID of the road, roadID cannot be changed after road creation
int Local::getRoadID() const {
    return roadID;
}

// SET methods
// Sets the name of the road
void Local::setName(const std::string& newName) {
    name = newName;
}

// Sets the description of the road
void Local::setDesc(const std::string& newDesc) {
    desc = newDesc;
}

// Sets the traffic status of the road
void Local::setTraffic(const std::string& newTraffic) {
    traffic = newTraffic;
}

// Sets the delay of the road
void Local::setDelay(int newDelay) {
    delay = newDelay;
}

// Sets the most popular hour of the road
void Local::setPopHour(int newPopHour) {
    popHour = newPopHour;
}

// Sets the construction status of the road
void Local::setConstruction(bool newConstruction) {
    construction = newConstruction;
}

// Sets the road ID of the road
void Local::setRoadID(int newRoadID) {
    roadID = newRoadID;
}


// HIGHWAY CLASS
// Constructor
Highway::Highway(const std::string& name, const std::string& desc, const std::string& traffic, int delay, int popHour, bool construction, int roadID) :
    name(name), desc(desc), traffic(traffic), delay(delay), popHour(popHour), construction(construction), roadID(roadID) {}

// GET methods
// Returns the name of the road
std::string Highway::getName() const {
    return name;
}

// Returns the description of the road
std::string Highway::getDesc() const {
    return desc;
}

// Returns the traffic status of the road
std::string Highway::getTraffic() const {
    return traffic;
}

// Returns "Highway" since it is a highway
std::string Highway::getType() const {
    return "Highway";
}

// Returns the approx. delay in minutes of the road
int Highway::getDelay() const {
    return delay;
}

// Returns the most popular hour (in 24 hour time) of the road
int Highway::getPopHour() const {
    return popHour;
}

// Returns True or False depending on if there is construction on the road
bool Highway::getConstruction() const {
    return construction;
}

// Returns the unique road ID of the road, roadID cannot be changed after road creation
int Highway::getRoadID() const {
    return roadID;
}

// SET methods
// Sets the name of the road
void Highway::setName(const std::string& newName) {
    name = newName;
}

// Sets the description of the road
void Highway::setDesc(const std::string& newDesc) {
    desc = newDesc;
}

// Sets the traffic status of the road
void Highway::setTraffic(const std::string& newTraffic) {
    traffic = newTraffic;
}

// Sets the delay of the road
void Highway::setDelay(int newDelay) {
    delay = newDelay;
}

// Sets the most popular hour of the road
void Highway::setPopHour(int newPopHour) {
    popHour = newPopHour;
}

// Sets the construction status of the road
void Highway::setConstruction(bool newConstruction) {
    construction = newConstruction;
}

// Sets the road ID of the road
void Highway::setRoadID(int newRoadID) {
    roadID = newRoadID;
}
