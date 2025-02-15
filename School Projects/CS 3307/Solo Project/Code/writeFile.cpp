#include "writeFile.h"
#include "road.h"
#include "roadFactory.h"
#include "user.h"
#include "userFactory.h"

// Default constructor
writeFile::writeFile() {};

// Method that will write to the accounts text file
void writeFile::writeUserFile(const std::string& file, std::vector<std::unique_ptr<User>>& userList) {
    // Opens the file in edit mode
    std::ofstream f(file);

    // Error handling to check if the file is opened
    if(!f.is_open()) {
        // Displays the error message and flushes the output afterwards
        std::cerr << "Error: Failed to open account database while writing." << std::endl;
    }

    // Temp variable to be written to file
    std::string temp;

    // Loops through the userList and writes the values into the file
    for(int i=0; i<userList.size(); i++) {

        // Gets the username and writes it to file
        temp = userList[i]->getUsername();
        f << temp << std::endl;

        // Gets the password and writes it to file
        temp = userList[i]->getPassword();
        f << temp << std::endl;

        // Gets the user type and writes it to file
        temp = userList[i]->getUserType();
        f << temp << std::endl;

        // Gets the watchlist and writes it to file
        temp = userList[i]->getWatchlist();
        f << temp << std::endl;
    }

    // Closes file at the end
    f.close();
}

// Method that will write to the road_database text file
void writeFile::writeRoadFile(const std::string& file, std::vector<std::unique_ptr<Road>>& roadList) {
    // Opens the file in edit mode
    std::ofstream f(file);

    // Error handling to check if the file is opened
    if(!f.is_open()) {
        // Displays the error message and flushes the output afterwards
        std::cerr << "Error: Failed to open road database while writing." << std::endl;
    }

    // Temp variable to be written to file
    std::string temp;

    // Loops through the userList and writes the values into the file
    for(int i=0; i<roadList.size(); i++) {

        // Gets the road name and writes it to file
        temp = roadList[i]->getName();
        f << temp << std::endl;

        // Gets the road description and writes it to file
        temp = roadList[i]->getDesc();
        f << temp << std::endl;

        // Gets the road traffic and writes it to file
        temp = roadList[i]->getTraffic();
        f << temp << std::endl;

        // Gets the road type and writes it to file
        temp = roadList[i]->getType();
        f << temp << std::endl;

        // Gets the road delay and writes it to file
        temp = std::to_string(roadList[i]->getDelay());
        f << temp << std::endl;

        // Gets the road popular hour and writes it to file
        temp = std::to_string(roadList[i]->getPopHour());
        f << temp << std::endl;

        // Gets the road construction and writes to file
        // Checks if getConstruction is true, if true then writes True
        if(roadList[i]->getConstruction()) {
            temp = "True";
            f << temp << std::endl;
        // If not true, then writes False
        } else {
            temp = "False";
            f << temp << std::endl;
        }

        // Gets the road ID and writes it to file
        temp = std::to_string(roadList[i]->getRoadID());
        f << temp << std::endl;
    }

    // Closes file at the end
    f.close();
}
