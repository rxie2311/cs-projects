#ifndef USER_H
#define USER_H

// C++ Libraries
#include <string>

// User Class
class User {
public:
    // Constructor
    User() = default;

    // GET methods
    virtual std::string getUsername() const = 0;
    virtual std::string getPassword() const = 0;
    virtual std::string getWatchlist() const = 0;
    virtual std::string getUserType() const = 0;

    // SET methods
    virtual void setUsername(const std::string& newUsername) = 0;
    virtual void setPassword(const std::string& newPass) = 0;
    virtual void setWatchlist(const std::string& newWatchlist) = 0;
};

// Concrete Class - Customer
class Customer : public User {
public:
    // Constructor
    Customer(const std::string& username, const std::string& password, const std::string& watchlist);

    // GET methods
    std::string getUsername() const override;
    std::string getPassword() const override;
    std::string getWatchlist() const override;
    std::string getUserType() const override;

    // SET methods
    void setUsername(const std::string& newUsername) override;
    void setPassword(const std::string& newPass) override;
    void setWatchlist(const std::string& newWatchlist) override;

private:
    // Instance variables
    std::string username;
    std::string password;
    std::string watchlist;
};

// Concrete Class - Employee
class Employee : public User {
public:
    // Constructor
    Employee(const std::string& username, const std::string& password, const std::string& watchlist);

    // GET methods
    std::string getUsername() const override;
    std::string getPassword() const override;
    std::string getWatchlist() const override;
    std::string getUserType() const override;

    // SET methods
    void setUsername(const std::string& newUsername) override;
    void setPassword(const std::string& newPass) override;
    void setWatchlist(const std::string& newWatchlist) override;

private:
    // Instance variables
    std::string username;
    std::string password;
    std::string watchlist;
};

// Concrete Class - Manager
class Manager : public User {
public:
    // Constructor
    Manager(const std::string& username, const std::string& password, const std::string& watchlist);

    // GET methods
    std::string getUsername() const override;
    std::string getPassword() const override;
    std::string getWatchlist() const override;
    std::string getUserType() const override;

    // SET methods
    void setUsername(const std::string& newUsername) override;
    void setPassword(const std::string& newPass) override;
    void setWatchlist(const std::string& newWatchlist) override;

private:
    // Instance variables
    std::string username;
    std::string password;
    std::string watchlist;
};

#endif // USER_H
