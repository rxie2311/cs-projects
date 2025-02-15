#include "loadFile.h"
#include "road.h"
#include "roadFactory.h"
#include "user.h"
#include "userFactory.h"

// Default constructor
loadFile::loadFile() {};

// Method that will compare two strings by converting both to lowercase and comparing them
bool loadFile::compareStr(const std::string& str1, const std::string& str2) {
    // If the two strings are not equal in length, then returns false
    if (str1.length() != str2.length())
        return false;

    // For loop to cycle through the length of one of the strings
    for (int i=0; i<str1.length(); i++) {
        // Compares each character in both strings by lowercasing both
        if (tolower(str1[i]) != tolower(str2[i]))
            // If the two characters do not match, then returns false
            return false;
    }

    // Returns true at the end if false was not returned
    return true;
}

// Method that will read the road_database text file and create a vector of Road objects
std::vector<std::unique_ptr<Road>> loadFile::createRoadList(const std::string& file) {
    // File and line variables for reading the file
    std::ifstream f(file);
    std::string line;

    // Error handling to check if the file is opened
    if(!f.is_open()) {
        // Displays the error message and flushes the output afterwards
        std::cerr << "Error: Failed to open road database." << std::endl;
    }

    // Temp vector variable to store all file lines
    std::vector<std::string> fileList;

    // While loop to loop through each line of the file and save into the vector
    while(getline(f, line)) {
        fileList.push_back(line);
    }

    // Closing file
    f.close();

    // Counter variable to track each line
    int counter = 0;

    // Temp variables
    std::string name;
    std::string desc;
    std::string traffic;
    std::string type;
    std::string delay;
    std::string popHour;
    bool construction;
    std::string roadID;
    std::unique_ptr<Road> road;

    // Vector to be returned at the end
    std::vector<std::unique_ptr<Road>> roadList;

    // For loop to loop through the temp vector variable
    for(const std::string& temp : fileList) {
        // Using switch case for saving lines
        switch(counter) {

        // Line 1: Road name
        case 0:
            // Saves index i in the vector into name
            name = temp;
            // Adds 1 to counter and breaks out of the switch case
            counter++;
            break;

        // Line 2: Road description
        case 1:
            // Saves index i in the vector into desc
            desc = temp;
            // Adds 1 to counter and breaks out of the switch case
            counter++;
            break;

        // Line 3: Road traffic
        case 2:
            // Saves index i in the vector into traffic
            traffic = temp;
            // Adds 1 to counter and breaks out of the switch case
            counter++;
            break;

        // Line 4: Road type
        case 3:
            // Saves index i in the vector into type
            type = temp;
            // Adds 1 to counter and breaks out of the switch case
            counter++;
            break;

        // Line 5: Road delay
        case 4:
            // Saves index i in the vector into delay
            delay = temp;
            // Adds 1 to counter and breaks out of the switch case
            counter++;
            break;

        // Line 6: Road's most popular hour
        case 5:
            // Saves index i in the vector into popHour
            popHour = temp;
            // Adds 1 to counter and breaks out of the switch case
            counter++;
            break;

        // Line 7: Road construction
        case 6:
            // If temp was indeed true, then saves true into construction
            if(compareStr(temp, "true")) {
                construction = true;
            // If not, then saves false into construction
            } else if(compareStr(temp, "false")) {
                construction = false;
            }
            // Adds 1 to counter and breaks out of the switch case
            counter++;
            break;

        // Line 8: Road ID, and object creation
        case 7:
            // Saves index i in the vector into roadID
            roadID = temp;

            // Creates a new road object using roadFactory and depending on type
            if(compareStr(type, "local")) {
                road = roadFactory::createRoad(roadFactory::roadType::Local, name, desc, traffic, std::stoi(delay), std::stoi(popHour), construction, std::stoi(roadID));
                // Moves the road object into the vector
                roadList.push_back(std::move(road));

            } else if(compareStr(type, "highway")) {
                road = roadFactory::createRoad(roadFactory::roadType::Highway, name, desc, traffic, std::stoi(delay), std::stoi(popHour), construction, std::stoi(roadID));
                // Moves the road object into the vector
                roadList.push_back(std::move(road));
            }

            // Reset counter back to 0 and break
            counter = 0;
            break;
        }
    }

    // Returns the vector with the roads in it at the end
    return roadList;
}

// Method that will read the accounts text file and create a vector of User objects
std::vector<std::unique_ptr<User>> loadFile::createUserList(const std::string& file) {
    // File and line variables for reading the file
    std::ifstream f(file);
    std::string line;

    // Error handling to check if the file is opened
    if(!f.is_open()) {
        // Displays the error message and flushes the output afterwards
        std::cerr << "Error: Failed to open account database." << std::endl;
    }

    // Temp vector variable to store all file lines
    std::vector<std::string> fileList;

    // While loop to loop through each line of the file and save into the vector
    while(getline(f, line)) {
        fileList.push_back(line);
    }

    // Closing the file
    f.close();

    // Counter variable to track each line
    int counter = 0;

    // Temp variables
    std::string username;
    std::string password;
    std::string type;
    std::string watchlist;
    std::unique_ptr<User> user;

    // Vector to be returned at the end
    std::vector<std::unique_ptr<User>> userList;

    // For loop to loop through the temp vector variable
    for(const std::string& temp : fileList) {
        // Using switch case for saving lines
        switch(counter) {

        // Line 1: Username
        case 0:
            // Saves index i in the vector into username
            username = temp;
            // Adds 1 to counter and breaks out of the switch case
            counter++;
            break;

        // Line 2: Password
        case 1:
            // Saves index i in the vector into password
            password = temp;
            // Adds 1 to counter and breaks out of the switch case
            counter++;
            break;

        // Line 3: User Type
        case 2:
            // Saves index i in the vector into type
            type = temp;
            // Adds 1 to counter and breaks out of the switch case
            counter++;
            break;

        // Line 4: Watchlist, and object creation
        case 3:
            // Saves index i in the vector into watchlist
            watchlist = temp;

            // Creates a new user object using userFactory and the type
            if(compareStr(type, "customer")) {
                // Creates a new Customer object
                user = userFactory::createUser(userFactory::userType::Customer, username, password, watchlist);
                // Moves the user object into the vector
                userList.push_back(std::move(user));

            } else if(compareStr(type, "employee")) {
                // Creates a new Customer object
                user = userFactory::createUser(userFactory::userType::Employee, username, password, watchlist);
                // Moves the user object into the vector
                userList.push_back(std::move(user));

            } else if(compareStr(type, "manager")) {
                // Creates a new Customer object
                user = userFactory::createUser(userFactory::userType::Manager, username, password, watchlist);
                // Moves the user object into the vector
                userList.push_back(std::move(user));
            }

            // Reset counter back to 0 and break
            counter = 0;
            break;
        }
    }

    // Returns the vector with the user objects
    return userList;
}
