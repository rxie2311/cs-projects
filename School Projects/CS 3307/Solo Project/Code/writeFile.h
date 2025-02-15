#ifndef WRITEFILE_H
#define WRITEFILE_H

// C++ Libraries
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Other Classes
#include "road.h"
#include "roadFactory.h"
#include "user.h"
#include "userFactory.h"

class writeFile {
public:
    // Default constructor
    writeFile();

    // Method to write to the accounts text file
    void writeUserFile(const std::string& file, std::vector<std::unique_ptr<User>>& userList);

    // Method to write to the road_database text file
    void writeRoadFile(const std::string& file, std::vector<std::unique_ptr<Road>>& roadList);
};

#endif // WRITEFILE_H
