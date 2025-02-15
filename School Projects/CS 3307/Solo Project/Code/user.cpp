#include "user.h"

// CUSTOMER CLASS
// Constructor method
Customer::Customer(const std::string& username, const std::string& password, const std::string& watchlist) :
    username(username), password(password), watchlist(watchlist) {}

// GET methods
// Returns the user's username
std::string Customer::getUsername() const {
    return username;
}

// Returns the user's password
std::string Customer::getPassword() const {
    return password;
}

// Returns the user's watchlist
std::string Customer::getWatchlist() const {
    return watchlist;
}

// Returns the user's account type
std::string Customer::getUserType() const {
    return "Customer";
}

// SET methods
// Sets the user's username
void Customer::setUsername(const std::string& newUsername) {
    username = newUsername;
}

// Sets the user's password
void Customer::setPassword(const std::string& newPass) {
    password = newPass;
}

// Sets the user's watchlist
void Customer::setWatchlist(const std::string& newWatchlist) {
    watchlist = newWatchlist;
}


// EMPLOYEE CLASS
// Constructor method
Employee::Employee(const std::string& username, const std::string& password, const std::string& watchlist) :
    username(username), password(password), watchlist(watchlist) {}

// GET methods
// Returns the user's username
std::string Employee::getUsername() const {
    return username;
}

// Returns the user's password
std::string Employee::getPassword() const {
    return password;
}

// Returns the user's watchlist
std::string Employee::getWatchlist() const {
    return watchlist;
}

// Returns the user's account type
std::string Employee::getUserType() const {
    return "Employee";
}

// SET methods
// Sets the user's username
void Employee::setUsername(const std::string& newUsername) {
    username = newUsername;
}

// Sets the user's password
void Employee::setPassword(const std::string& newPass) {
    password = newPass;
}

// Sets the user's watchlist
void Employee::setWatchlist(const std::string& newWatchlist) {
    watchlist = newWatchlist;
}


// MANAGER CLASS
// Constructor method
Manager::Manager(const std::string& username, const std::string& password, const std::string& watchlist) :
    username(username), password(password), watchlist(watchlist) {}

// GET methods
// Returns the user's username
std::string Manager::getUsername() const {
    return username;
}

// Returns the user's password
std::string Manager::getPassword() const {
    return password;
}

// Returns the user's watchlist
std::string Manager::getWatchlist() const {
    return watchlist;
}

// Returns the user's account type
std::string Manager::getUserType() const {
    return "Manager";
}

// SET methods
// Sets the user's username
void Manager::setUsername(const std::string& newUsername) {
    username = newUsername;
}

// Sets the user's password
void Manager::setPassword(const std::string& newPass) {
    password = newPass;
}

// Sets the user's watchlist
void Manager::setWatchlist(const std::string& newWatchlist) {
    watchlist = newWatchlist;
}
