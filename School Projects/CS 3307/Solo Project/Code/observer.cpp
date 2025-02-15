#include "observer.h"

// Method that will update the displays when the road attributes change
std::string Display::update(const std::string& name, int delay, int popHour, const std::string& traffic, bool constr) const {
    // String variable to piece together a status update message
    std::string updateMsg;

    // Creating the update message
    // Header of the message
    updateMsg += "Road " + name + " has been updated:\n";
    // New delay
    updateMsg += "New delay >> " + std::to_string(delay) + " minutes \n";
    // New popular hour
    updateMsg += "New popular hour >> " + std::to_string(popHour) + ":00 \n";
    // New traffic status
    updateMsg += "New traffic status >> " + traffic + " \n";
    // New construction status
    if(constr == true) {
        updateMsg += "New construction status >> True \n\n";
    } else {
        updateMsg += "New construction status >> False \n\n";
    }

    // Returns the update message at the end
    return updateMsg;
}
