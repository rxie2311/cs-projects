#ifndef USERFACTORY_H
#define USERFACTORY_H

// C++ Libraries
#include <memory>
#include <string>

// Other Classes
#include "user.h"

// userFactory class - For the factory design pattern
class userFactory {
public:
    // Constant variables for the three types of users
    enum class userType { Customer, Employee, Manager };
    // createUser method that creates a new User object
    static std::unique_ptr<User> createUser(userType type, const std::string& username, const std::string& password, const std::string& watchlist);
};

#endif // USERFACTORY_H
