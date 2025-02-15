#ifndef ROADWATCHER_H
#define ROADWATCHER_H

// C++ Libraries
#include <string>
#include <vector>

// Other Classes
#include "observer.h"

// Road Watcher Class (Subject Class that the observer will observe)
class roadWatcher {
public:
    // Method that registers a new observer
    void registerObserver(Observer* observer);

    // Method to notify observers when a change has been detected
    std::string notify();

    // Method to set the instance variables to the parameters and call on notify
    std::string setValues(const std::string& name, int delay, int popHour, const std::string& traffic, bool constr);

private:
    // Instance variables
    std::string newName;
    int newDelay;
    int newPopHour;
    std::string newTraffic;
    bool newConstr;

    // Observer list
    std::vector<Observer*> observers;
};

#endif // ROADWATCHER_H
