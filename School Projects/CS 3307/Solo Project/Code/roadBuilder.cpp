#include "roadBuilder.h"
#include "road.h"

// Local Builder Class
// Builds the road name
void localBuilder::buildName(const std::string& newName) {
    name = newName;
}

// Builds the road description
void localBuilder::buildDesc(const std::string& newDesc) {
    desc = newDesc;
}

// Builds the traffic status
void localBuilder::buildTraffic(const std::string& newTraffic) {
    traffic = newTraffic;
}

// Builds the delay of the road
void localBuilder::buildDelay(int newDelay) {
    delay = newDelay;
}

// Builds the most popular hour of the road
void localBuilder::buildPopHour(int newPopHour) {
    popHour = newPopHour;
}

// Builds the construction status of the road
void localBuilder::buildConstruction(bool newConstruction) {
    constr = newConstruction;
}

// Builds the road ID of the road
void localBuilder::buildRoadID(int newRoadID) {
    roadID = newRoadID;
}

// Method that returns the built local road
std::unique_ptr<Road> localBuilder::getRoad() {
    return std::make_unique<Local>(name, desc, traffic, delay, popHour, constr, roadID);
}


// Highway Builder Class
// Builds the road name
void highwayBuilder::buildName(const std::string& newName) {
    name = newName;
}

// Builds the road description
void highwayBuilder::buildDesc(const std::string& newDesc) {
    desc = newDesc;
}

// Builds the traffic status
void highwayBuilder::buildTraffic(const std::string& newTraffic) {
    traffic = newTraffic;
}

// Builds the delay of the road
void highwayBuilder::buildDelay(int newDelay) {
    delay = newDelay;
}

// Builds the most popular hour of the road
void highwayBuilder::buildPopHour(int newPopHour) {
    popHour = newPopHour;
}

// Builds the construction status of the road
void highwayBuilder::buildConstruction(bool newConstruction) {
    constr = newConstruction;
}

// Builds the road ID of the road
void highwayBuilder::buildRoadID(int newRoadID) {
    roadID = newRoadID;
}

// Method that returns the built highway road
std::unique_ptr<Road> highwayBuilder::getRoad() {
    return std::make_unique<Highway>(name, desc, traffic, delay, popHour, constr, roadID);
}
