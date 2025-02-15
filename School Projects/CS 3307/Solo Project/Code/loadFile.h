#ifndef LOADFILE_H
#define LOADFILE_H

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

// Class used to read from the files and store into lists
class loadFile {
public:
    // Default constructor
    loadFile();

    // Method to compare two strings (non-case sensitive)
    bool compareStr(const std::string& str1, const std::string& str2);

    // Method to read from the road_database text file and return a list of Road objects
    std::vector<std::unique_ptr<Road>> createRoadList(const std::string& file);

    // Method to read from the accounts text file and return a list of User objects
    std::vector<std::unique_ptr<User>> createUserList(const std::string& file);
};

#endif // LOADFILE_H
