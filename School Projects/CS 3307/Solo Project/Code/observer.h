#ifndef OBSERVER_H
#define OBSERVER_H

// C++ Libraries
#include <string>

// Observer Class - For Observer Pattern
class Observer {
public:
    // Method that will update the displays when the road attributes change
    virtual std::string update(const std::string& name, int delay, int popHour, const std::string& traffic, bool constr) const = 0;
};

// Display Class (Concrete Observer)
class Display : public Observer {
public:
    // Method that will update the displays when the road attributes change
    std::string update(const std::string& name, int delay, int popHour, const std::string& traffic, bool constr) const override;
};

#endif // OBSERVER_H
