#include "roadWatcher.h"

// Method that registers a new observer
void roadWatcher::registerObserver(Observer* observer) {
    // Saves the observer into the observer list
    observers.push_back(observer);
}

// Method to notify observers when a change has been detected
std::string roadWatcher::notify() {
    // Temp variable to save the output of update()
    std::string updateMsg;

    // For loop to cycle through all of the observers in the observer list
    for(Observer* observer : observers) {
        // Calls on update on each one to update them
        updateMsg = observer->update(newName, newDelay, newPopHour, newTraffic, newConstr);
    }

    // Returns updateMsg
    return updateMsg;
}

// Method to set the instance variables to the parameters and call on notify
std::string roadWatcher::setValues(const std::string& name, int delay, int popHour, const std::string& traffic, bool constr) {
    // Setting all instance variables inside of the class with the parameters inputted
    newName = name;
    newDelay = delay;
    newPopHour = popHour;
    newTraffic = traffic;
    newConstr = constr;

    // Temp variable to save the output of update()
    std::string updateMsg;

    // Calls on notify to notify all observers of a change
    updateMsg = notify();

    // Returns the update message from the observers
    return updateMsg;
}
