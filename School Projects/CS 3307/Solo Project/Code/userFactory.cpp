#include "userFactory.h"

// createUser method that will create User objects
std::unique_ptr<User> userFactory::createUser(userType type, const std::string& username, const std::string& password, const std::string& watchlist) {
    // Checks which type is passed into the method
    switch(type) {
    // If the user type is Customer
    case userType::Customer:
        return std::make_unique<Customer>(username, password, watchlist);
    // If the user type is Employee
    case userType::Employee:
        return std::make_unique<Employee>(username, password, watchlist);
    // If the user type is Manager
    case userType::Manager:
        return std::make_unique<Manager>(username, password, watchlist);
    // If the type was not one of the constant ones, then return null
    default:
        return nullptr;
    }
}
