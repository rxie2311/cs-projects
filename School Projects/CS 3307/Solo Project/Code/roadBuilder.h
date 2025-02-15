#ifndef ROADBUILDER_H
#define ROADBUILDER_H

// C++ Libraries
#include <iostream>
#include <memory>
#include <string>

// Other Classes
#include "road.h"

// Road Builder - Abstract Builder Class
class roadBuilder {
public:
    // Builder methods
    virtual void buildName(const std::string& newName) = 0;
    virtual void buildDesc(const std::string& newDesc) = 0;
    virtual void buildTraffic(const std::string& newTraffic) = 0;
    virtual void buildDelay(int newDelay) = 0;
    virtual void buildPopHour(int newPopHour) = 0;
    virtual void buildConstruction(bool newConstruction) = 0;
    virtual void buildRoadID(int newRoadID) = 0;

    // Method that returns the built road when called
    virtual std::unique_ptr<Road> getRoad() = 0;
};

// Local Builder - Concrete Builder Class
class localBuilder : public roadBuilder {
public:
    // Builder methods
    void buildName(const std::string& newName) override;
    void buildDesc(const std::string& newDesc) override;
    void buildTraffic(const std::string& newTraffic) override;
    void buildDelay(int newDelay) override;
    void buildPopHour(int newPopHour) override;
    void buildConstruction(bool newConstruction) override;
    void buildRoadID(int newRoadID) override;

    // Method that returns the built road when called
    std::unique_ptr<Road> getRoad() override;

private:
    // Instance variables
    std::string name;
    std::string desc;
    std::string traffic;
    int delay;
    int popHour;
    bool constr;
    int roadID;
};

// Highway Builder - Concrete Builder Class
class highwayBuilder : public roadBuilder {
public:
    // Builder methods
    void buildName(const std::string& newName) override;
    void buildDesc(const std::string& newDesc) override;
    void buildTraffic(const std::string& newTraffic) override;
    void buildDelay(int newDelay) override;
    void buildPopHour(int newPopHour) override;
    void buildConstruction(bool newConstruction) override;
    void buildRoadID(int newRoadID) override;

    // Method that returns the built road when called
    std::unique_ptr<Road> getRoad() override;

private:
    // Instance variables
    std::string name;
    std::string desc;
    std::string traffic;
    int delay;
    int popHour;
    bool constr;
    int roadID;
};

#endif // ROADBUILDER_H
