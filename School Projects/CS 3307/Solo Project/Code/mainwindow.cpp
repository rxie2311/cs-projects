#include "mainwindow.h"
#include "ui_mainwindow.h"
// Object Classes
#include "road.h"
#include "roadFactory.h"
#include "user.h"
#include "userFactory.h"
// File Management Classes
#include "loadFile.h"
#include "writeFile.h"
// Observer Pattern Classes
#include "roadWatcher.h"
#include "observer.h"
// Builder Pattern Class
#include "roadBuilder.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Helper Methods
// When this method is called, generates the lists and saves into the instance variable
void MainWindow::generateList() {
    // Creates a loadFile object for list generation
    loadFile obj;
    // Generates a vector of Road objects
    roadList = obj.createRoadList("road_database.txt");
    // Generates a vector of User objects
    userList = obj.createUserList("accounts.txt");
}

// When this method is called, fill the list widget with road names
void MainWindow::fillListWidget() {
    // Row counter variable
    int row = 1;
    // Iterates through the road list with all the roads from the database file
    for(int i=0; i<roadList.size(); i++) {
        // Creates a new QListWidgetItem
        QListWidgetItem *newItem = new QListWidgetItem;
        // Saves the name of the Road object at index i as the text of the new item
        newItem->setText(QString::fromStdString(roadList[i]->getName()));
        // Inserts the new item in a row tracked by the row counter
        ui->road_list->insertItem(row, newItem);
        // Adds 1 to the row counter so each item is placed neatly in rows
        row++;
    }
}

// When this method is called, registers the display into the observer list
void MainWindow::linkDisplay() {
    // Registers the display as an observer (this display will be the sole observer responsible for the entire user session)
    roadWatch.registerObserver(&display);
}

// When this method is called, helps split the string parameter by comma (simulates the .split() function in Java)
std::vector<int> MainWindow::splitString(std::string& str) {
    // Create a temp vector to store the string that needs to be split
    std::vector<int> splitStr;

    // Uses stringstream to create a stream
    std::stringstream ss(str);

    // For loop to cycle through the string stream and discard commas
    for(int i; ss >> i;) {
        splitStr.push_back(i);
        if(ss.peek() == ',') {
            ss.ignore();
        }
    }

    // Returns the split up string in a vector
    return splitStr;
}


// GUI Methods
// PAGE 1: LOG IN SCREEN
// When user clicks the log in button, takes them to page 2 (main page)
void MainWindow::on_log_in_clicked()
{
    // Takes the input from the username and password text boxes
    QString username = ui->username_text->toPlainText();
    QString password = ui->pass_text->toPlainText();

    // Flag variable to determine if user successfully logged in or not
    bool login = false;

    // For loop to iterate through user vector
    for(int i=0; i<userList.size(); i++) {
        // Compares the username and password inputted to each index (case-sensitive)
        // If the username and password match one of the username + password combo in the user vector
        if(username.toStdString() == userList[i]->getUsername() && password.toStdString() == userList[i]->getPassword()) {
            // Sets the login flag to true
            login = true;

            // Saves the current user information into currUser object for the session
            loadFile obj;
            if(obj.compareStr(userList[i]->getUserType(), "customer")) {
                currUser = userFactory::createUser(userFactory::userType::Customer, userList[i]->getUsername(), userList[i]->getPassword(), userList[i]->getWatchlist());

            } else if(obj.compareStr(userList[i]->getUserType(), "employee")) {
                currUser = userFactory::createUser(userFactory::userType::Employee, userList[i]->getUsername(), userList[i]->getPassword(), userList[i]->getWatchlist());

            } else if(obj.compareStr(userList[i]->getUserType(), "manager")) {
                currUser = userFactory::createUser(userFactory::userType::Manager, userList[i]->getUsername(), userList[i]->getPassword(), userList[i]->getWatchlist());
            }

            // Calls on helper method to generate text for the list widget
            fillListWidget();
            // Takes the user to the main menu
            ui->stackedWidget->setCurrentIndex(1);
            // Clears out the username and password text boxes
            ui->username_text->clear();
            ui->pass_text->clear();
            // Clears out the status message label after a successful login
            ui->status_label->clear();
        }
    }

    // If the login flag is still false
    if(!login) {
        // Informs the user that they entered the wrong credentials
        ui->status_label->setText("Incorrect username or password, try again.");
        ui->status_label->setAlignment(Qt::AlignCenter);
    }
}


// PAGE 2: MAIN MENU
// When user clicks the log out button, takes them to page 1 (login page)
void MainWindow::on_log_out_clicked()
{
    // CLEAR STATEMENTS - Clearing all text boxes and labels when user logs out
    // Clears the list widget, so there will not be dupes of Road objects when user relogs in
    ui->road_list->clear();
    // Clears the text editor, so the details of the last road viewed is cleared
    ui->road_atts->clear();
    // Clears the watchlist status message if there was one
    ui->watchlist_status->clear();
    // Clears the watched roads text box
    ui->watched_roads->clear();
    // Clears any denial message if there was one
    ui->perms_label->clear();
    // Clears the watchlist report text box
    ui->report->clear();

    // Page 1 = Index 0
    ui->stackedWidget->setCurrentIndex(0);
}

// When user clicks the watchlist button, takes them to page 3 (watchlist page)
void MainWindow::on_watchlist_clicked()
{
    // Store the current user's watchlist into temp string
    std::string tempWatch = currUser->getWatchlist();
    // Call on splitString to turn it into a vector
    std::vector<int> watchlist = splitString(tempWatch);

    // Temp variable to store all the watchlist road names
    QString roadNames;
    // Nested for loop to compare watchlist vector and road list vector
    for(int i=0; i<roadList.size(); i++) {
        for(int j=0; j<watchlist.size(); j++) {
            // If the road IDs match, saves the road name into the temp variable
            if(watchlist[j] == roadList[i]->getRoadID()) {
                roadNames += roadList[i]->getName() + "\n";
            }
        }
    }

    // Adding the temp variable with all the road names into the text widget
    ui->watched_roads->setText(roadNames);

    // Clears any denial message if there was one (if the user clicked on the Employee and Manager buttons)
    ui->perms_label->clear();

    // Page 3 = Index 2
    ui->stackedWidget->setCurrentIndex(2);
}

// When user clicks on the search button, take them to the search page
void MainWindow::on_search_clicked()
{
    // Clears any denial message if there was one (if the user clicked on the Employee and Manager buttons)
    ui->perms_label->clear();

    // Page 6 = Index 5
    ui->stackedWidget->setCurrentIndex(5);
}

// When user clicks on an item in the list widget, display attributes of that road (item clicked)
void MainWindow::on_road_list_itemClicked(QListWidgetItem *item)
{
    // Grabs the row number
    int row = ui->road_list->currentRow();

    // Clears the text box
    ui->road_atts->clear();

    // Adds all the attributes to a single temp variable
    QString attributes;
    // Road Name
    attributes += "Road Name: " + roadList[row]->getName() + "\n\n";
    // Road Description
    attributes += "Road Description: " + roadList[row]->getDesc() + "\n\n";
    // Road Type
    attributes += "Road Type: " + roadList[row]->getType() + "\n\n";
    // Road Traffic
    attributes += "Current Traffic Status: " + roadList[row]->getTraffic() + "\n\n";
    // Road Delay in minutes
    attributes += "Current Delay: " + std::to_string(roadList[row]->getDelay()) + " minutes\n\n";
    // Most Popular Hour of Road
    attributes += "Most Popular Hour: " + std::to_string(roadList[row]->getPopHour()) + ":00\n\n";
    // Construction
    if(roadList[row]->getConstruction() == true) {
        // If getConstruction returns True
        attributes += "ALERT: Road is currently undergoing construction!\n\n";

    } else {
        // If getConstruction returns False
        attributes += "Road is currently not undergoing construction.\n\n";
    }
    // Road ID
    attributes += "Road ID: " + std::to_string(roadList[row]->getRoadID()) + "\n\n";

    // Adding the temp variable with all attributes to the text widget
    ui->road_atts->setText(attributes);
}

// Method that adds the road that the user has selected in the list into the user's watchlist
void MainWindow::on_add_watchlist_clicked()
{
    // Clears the watchlist status message if there was one
    ui->watchlist_status->clear();

    // Grabs the row number
    int row = ui->road_list->currentRow();

    // Grabs the road ID of the road currently selected
    int id = roadList[row]->getRoadID();

    // Calls on string split to split the current user's watchlist into a vector
    std::string tempWatch = currUser->getWatchlist();
    std::vector<int> watchlist = splitString(tempWatch);
    // Variable flag to check for dupe road IDs within the watchlist
    bool dupeRoad = false;

    // Cycles through the watchlist to check for dupes
    for(int i=0; i<watchlist.size(); i++) {
        // If a dupe ID is found
        if(id == watchlist[i]) {
            // Sets the flag to true and breaks out
            dupeRoad = true;
            break;
        }
    }

    // If there was no dupe road ID, then saves the watchlisted road ID into the user's account
    if(!dupeRoad) {
        // Temp variable to store current user's watchlist and add the new road to it
        tempWatch += std::to_string(id) + ",";

        // Updates current user's watchlist
        currUser->setWatchlist(tempWatch);

        // Variable used as a flag when the user's watchlist has been updated
        bool updated = false;

        // Cycles through the user list to find where current user is in the list
        for(int i=0; i<userList.size(); i++) {
            if(currUser->getUsername() == userList[i]->getUsername() && currUser->getPassword() == userList[i]->getPassword()) {
                userList[i]->setWatchlist(tempWatch);
                updated = true;
            }
        }

        // If the flag has been set to true, write the new user vector to the file
        if(updated) {
            writeFile obj;
            obj.writeUserFile("accounts.txt", userList);
        }

        // Lets the user know via status message
        ui->watchlist_status->setText("Road successfully added!");
        ui->watchlist_status->setStyleSheet("QLabel { color: rgb(0, 255, 0); }");
        ui->watchlist_status->setAlignment(Qt::AlignCenter);

    // If there was a dupe road ID, then lets the user know via a label
    } else {
        ui->watchlist_status->setText("Road is already in watchlist!");
        ui->watchlist_status->setStyleSheet("QLabel { color: rgb(255, 0, 0); }");
        ui->watchlist_status->setAlignment(Qt::AlignCenter);
    }
}

// Method that removes the road that the user has selected in the list from their watchlist
void MainWindow::on_remove_watchlist_clicked()
{
    // Clears the watchlist status message if there was one
    ui->watchlist_status->clear();

    // Grabs the row number
    int row = ui->road_list->currentRow();

    // Grabs the road ID of the road currently selected
    int id = roadList[row]->getRoadID();

    // Calls on string split to split the current user's watchlist into a vector
    std::string tempWatch = currUser->getWatchlist();
    std::vector<int> watchlist = splitString(tempWatch);
    // Variable flag to check for the road in the user's watchlist
    bool foundRoad = false;

    // Cycles through the watchlist to check for the road the user wants to remove
    for(int i=0; i<watchlist.size(); i++) {
        // If the road ID that is to be removed is found in the watchlist
        if(id == watchlist[i]) {
            // Sets the flag to true
            foundRoad = true;
            // Removes the road index from the watchlist vector
            watchlist.erase(watchlist.begin() + i);
            // Sets tempWatch to empty
            tempWatch = "";
            // Breaks out of the loop
            break;
        }
    }

    // If the road ID was found the user's watchlist, then removes it from the user's watchlist
    if(foundRoad) {
        // Cycles through the watchlist vector and appends all road IDs into tempWatch
        for(int i=0; i<watchlist.size(); i++) {
            tempWatch += std::to_string(watchlist[i]) + ",";
        }

        // Updates current user's watchlist
        currUser->setWatchlist(tempWatch);

        // Variable used as a flag when the user's watchlist has been updated
        bool updated = false;

        // Cycles through the user list to find where current user is in the list
        for(int i=0; i<userList.size(); i++) {
            if(currUser->getUsername() == userList[i]->getUsername() && currUser->getPassword() == userList[i]->getPassword()) {
                userList[i]->setWatchlist(tempWatch);
                updated = true;
            }
        }

        // If the flag has been set to true, write the new user vector to the file
        if(updated) {
            writeFile obj;
            obj.writeUserFile("accounts.txt", userList);
        }

        // Lets the user know via status message
        ui->watchlist_status->setText("Road successfully removed!");
        ui->watchlist_status->setStyleSheet("QLabel { color: rgb(0, 255, 0); }");
        ui->watchlist_status->setAlignment(Qt::AlignCenter);

    // If there was a dupe road ID, then lets the user know via a label
    } else {
        ui->watchlist_status->setText("Road not in watchlist!");
        ui->watchlist_status->setStyleSheet("QLabel { color: rgb(255, 0, 0); }");
        ui->watchlist_status->setAlignment(Qt::AlignCenter);
    }
}

// Method that takes the user to the edit road attributes page IF they are user type Employee or higher
void MainWindow::on_edit_road_clicked()
{
    // Checks if the user's account type is Employee or Manager level
    if(currUser->getUserType() == "Employee" || currUser->getUserType() == "Manager") {
        // Clears any denial message if there was one
        ui->perms_label->clear();
        // Takes the user to page 4 (index 3)
        ui->stackedWidget->setCurrentIndex(3);

    // If the user's account type is only Customer level
    } else {
        ui->perms_label->setText("No perms.");
        ui->perms_label->setAlignment(Qt::AlignCenter);
    }
}

// Method that takes the user to the add road page IF they are user type Manager
void MainWindow::on_add_road_clicked()
{
    if(currUser->getUserType() == "Manager") {
        // Clears any denial message if there was one
        ui->perms_label->clear();
        // Takes the user to page 5 (index 4)
        ui->stackedWidget->setCurrentIndex(4);

    // If the user's account type is Customer or Employee level
    } else {
        ui->perms_label->setText("No perms.");
        ui->perms_label->setAlignment(Qt::AlignCenter);
    }
}


// PAGE 3: WATCHLIST
// When user clicks the back button, takes them back to page 2 (main menu)
void MainWindow::on_back_to_menu_clicked()
{
    // Page 2 = Index 1
    ui->stackedWidget->setCurrentIndex(1);
}


// PAGE 4: EDIT ROAD ATTRIBUTES PAGE
// When the user clicks the back button, takes them back to page 2 (main menu)
void MainWindow::on_back_to_menu_2_clicked()
{
    // Clears all of the attribute fields
    ui->id_text->clear();
    ui->delay_text->clear();
    ui->pop_hour_text->clear();
    ui->traffic_text->clear();
    ui->constr_text->clear();
    // Clears the status label in case something was in there
    ui->submit_status->clear();
    // Page 2 = Index 1
    ui->stackedWidget->setCurrentIndex(1);
}

// When the user clicks on the submit button, checks if values entered are correct
void MainWindow::on_submit_clicked()
{
    // Saves the user input at the road ID text box
    std::string strID = ui->id_text->toPlainText().toStdString();
    int roadID;

    // Checking if an empty string was entered
    if(ui->id_text->toPlainText().isEmpty()) {
        // If an empty string was entered, sets roadID to -1 (no road matches that)
        roadID = -1;
    } else {
        // If an empty string was not entered, saves it into roadID
        roadID = std::stoi(strID);
    }

    // Variable flag to determine if all fields are correctly inputted
    bool correct = false;
    // Temp variable to store user inputted values
    std::string userInput;
    int userDelay;
    int userPopHour;
    std::string userTraffic;
    bool userConstr;

    // For loop to cycle through the road list to see if the ID inputted matches with an ID in the list
    for(int i=0; i<roadList.size(); i++) {
        if(roadID == roadList[i]->getRoadID()) {
            // Checking if an empty string was entered
            if(ui->delay_text->toPlainText().isEmpty()) {
                break;
            }

            // Saving the user's inputted delay value
            userInput = ui->delay_text->toPlainText().toStdString();
            userDelay = std::stoi(userInput);

            // Checking if user's other inputs follow the rules, must pass all 3 tests to save the attribute changes and update file
            loadFile obj;

            // Test 1: Checking popular hour for an int from 0 to 23
            // Checking if an empty string was entered
            if(ui->pop_hour_text->toPlainText().isEmpty()) {
                break;
            }

            // If not, then saves user input
            userInput = ui->pop_hour_text->toPlainText().toStdString();
            // If the user's inputted popular hour is not in the range of 0-23, then break
            if(std::stoi(userInput) < 0 || std::stoi(userInput) > 23 ) {
                break;
            } else {
                userPopHour = std::stoi(userInput);
            }

            // Test 2: Checking traffic status for either "light" or "heavy"
            userInput = ui->traffic_text->toPlainText().toStdString();
            // If the user's inputted string is equal to either "light" or "heavy"
            if(obj.compareStr(userInput, "light")) {
                userTraffic = "Light";
            } else if(obj.compareStr(userInput, "heavy")) {
                userTraffic = "Heavy";
            } else {
                break;
            }

            // Test 3: Checking construction status for either "true" or "false"
            userInput = ui->constr_text->toPlainText().toStdString();
            // If the user's inputted string is equal to "true"
            if(obj.compareStr(userInput, "true")) {
                userConstr = true;
            // If the user's inputted string is equal to "false"
            } else if(obj.compareStr(userInput, "false")) {
                userConstr = false;
            // If it is neither, then break
            } else {
                break;
            }

            // Once all 3 tests have been passed, then sets the flag to true
            correct = true;
            // Starts updating the road at index i with the new attributes
            roadList[i]->setDelay(userDelay);
            roadList[i]->setPopHour(userPopHour);
            roadList[i]->setTraffic(userTraffic);
            roadList[i]->setConstruction(userConstr);

            // Writes the changes to the file
            writeFile writeObj;
            writeObj.writeRoadFile("road_database.txt", roadList);

            // OBSERVER: Updating the notifications text box if the updated road is one in the user's watchlist
            // Calls on string split to split the current user's watchlist into a vector
            std::string tempWatch = currUser->getWatchlist();
            std::vector<int> watchlist = splitString(tempWatch);

            // Checks if the road ID of the updated road is in the user's watchlist
            for(int j=0; j<watchlist.size(); j++) {
                if(roadID == watchlist[j]) {
                    // Creates a new temp variable to store the update message
                    std::string updateMsg;
                    // Updates the observer subject to trigger the observer
                    updateMsg = roadWatch.setValues(roadList[i]->getName(), roadList[i]->getDelay(), roadList[i]->getPopHour(), roadList[i]->getTraffic(), roadList[i]->getConstruction());

                    // Updates the watchlist report text box
                    ui->report->append(QString::fromStdString(updateMsg));
                    // Breaks out of the road ID check loop
                    break;
                }
            }

            // Lets the user know that the attributes have been updated with a status message
            // Clears the status label in case something was in there
            ui->submit_status->clear();

            ui->submit_status->setText("Success: Road has been updated!");
            ui->submit_status->setStyleSheet("QLabel { color: rgb(0, 255, 0); }");
            ui->submit_status->setAlignment(Qt::AlignCenter);

            // Breaks out of the loop
            break;
        }
    }

    // Checks if the correct flag is still false, if it is, then lets the user know that the info entered is incorrect
    if(correct == false) {
        // Clears the status label in case something was in there
        ui->submit_status->clear();

        ui->submit_status->setText("Error: Invalid value entered!");
        ui->submit_status->setStyleSheet("QLabel { color: rgb(255, 0, 0); }");
        ui->submit_status->setAlignment(Qt::AlignCenter);
    }
}


// PAGE 5: ADD ROADS PAGE
// When the user clicks the back button, takes them back to page 2 (main menu)
void MainWindow::on_back_to_menu_3_clicked()
{
    // Clears all of the text boxes
    ui->id_text_2->clear();
    ui->name_text_2->clear();
    ui->desc_text_2->clear();
    ui->traffic_text_2->clear();
    ui->delay_text_2->clear();
    ui->popHour_text_2->clear();
    ui->constr_text_2->clear();
    ui->type_text_2->clear();

    // Clears the status label in case something was in there
    ui->submit_status_2->clear();

    // Refreshes the list widget so added roads show up immedietely
    ui->road_list->clear();
    fillListWidget();

    // Page 2 = Index 1
    ui->stackedWidget->setCurrentIndex(1);
}

// When the user clicks on the submit button, checks if values entered are correct
void MainWindow::on_submit_2_clicked()
{
    // Variable flag to determine if all fields are correctly inputted
    bool correct = true;

    // CHECK 0: ROAD ID
    // Saves the user input at the road ID text box
    std::string strID = ui->id_text_2->toPlainText().toStdString();
    int roadID;

    // Checking if an empty string was entered
    if(ui->id_text_2->toPlainText().isEmpty()) {
        // If an empty string was entered, sets correct to false
        correct = false;
    // Checking if the road ID entered is greater than 1
    } else if(std::stoi(ui->id_text_2->toPlainText().toStdString()) < 1) {
        // If road ID entered was smaller than 1, then sets correct to false
        correct = false;
    // If no empty string was entered, and road ID entered was greater than 1, then saves it into roadID
    } else {
        // If an empty string was not entered, saves it into roadID
        roadID = std::stoi(strID);
    }

    // For loop to cycle through the road list to see if the ID inputted matches with an ID in the list
    for(int i=0; i<roadList.size(); i++) {
        // If there is a match, then set correct to false
        if(roadID == roadList[i]->getRoadID()) {
            correct = false;
        }
    }

    // Temp variable to store user inputted values
    std::string name;
    std::string traffic;
    int delay;
    int popHour;
    bool constr;
    std::string desc;
    std::string type;

    // Creating a loadFile object for string comparison
    loadFile obj;
    // Creating a temp variable if needed for comparison checks
    std::string userInput;

    // Performs a check on each text box to ensure the values entered are correct
    // CHECK 1: ROAD NAME
    if(ui->name_text_2->toPlainText().isEmpty()) {
        // If an empty string was entered, sets correct to false
        correct = false;
    } else {
        // If an empty string was not entered, saves it into name
        name = ui->name_text_2->toPlainText().toStdString();
    }

    // CHECK 2: ROAD TRAFFIC STATUS
    userInput = ui->traffic_text_2->toPlainText().toStdString();
    // Checks if the user input for traffic was "light"
    if(obj.compareStr(userInput, "light")) {
        traffic = "Light";
    // Checks if the user input for traffic was "heavy"
    } else if(obj.compareStr(userInput, "heavy")) {
        traffic = "Heavy";
    // If neither, then sets correct to false
    } else {
        correct = false;
    }

    // CHECK 3: ROAD DELAY
    // Checking if an empty string was entered
    if(ui->delay_text_2->toPlainText().isEmpty()) {
        correct = false;
    // If an empty string was not entered, save it into delay
    } else {
        delay = std::stoi(ui->delay_text_2->toPlainText().toStdString());
    }

    // CHECK 4: ROAD POPULAR HOUR
    userInput = ui->popHour_text_2->toPlainText().toStdString();
    // Checking if an empty string was entered
    if(ui->popHour_text_2->toPlainText().isEmpty()) {
        correct = false;
    // If an empty string was not entered, checks if the int entered is within range
    } else if(std::stoi(userInput) < 0 || std::stoi(userInput) > 23 ) {
        correct = false;
    // If within range, saves into popHour
    } else {
        popHour = std::stoi(userInput);
    }

    // CHECK 5: CONSTRUCTION STATUS
    userInput = ui->constr_text_2->toPlainText().toStdString();
    // If the user's inputted string is equal to "true"
    if(obj.compareStr(userInput, "true")) {
        constr = true;
    // If the user's inputted string is equal to "false"
    } else if(obj.compareStr(userInput, "false")) {
        constr = false;
    // If it is neither, then correct gets updated to false
    } else {
        correct = false;
    }

    // CHECK 6: ROAD DESCRIPTION
    if(ui->desc_text_2->toPlainText().isEmpty()) {
        // If an empty string was entered, sets correct to false
        correct = false;
    } else {
        // If an empty string was not entered, saves it into name
        desc = ui->desc_text_2->toPlainText().toStdString();
    }

    // CHECK 7: ROAD TYPE
    userInput = ui->type_text_2->toPlainText().toStdString();
    // If the user's inputted string is equal to "local"
    if(obj.compareStr(userInput, "local")) {
        type = "Local";
    // If the user's inputted string is equal to "highway"
    } else if(obj.compareStr(userInput, "highway")) {
        type = "Highway";
    // If neither, then sets correct to false
    } else {
        correct = false;
    }

    // If correct is still true after the 7 checks, then calls on builder to start building an object
    if(correct) {
        // If the user inputted a road type Local, then creates a new local object and saves it into the roadList and updates the file
        if(type == "Local") {
            // Creates a new Local builder
            localBuilder builder;

            // Starts building the road
            builder.buildRoadID(roadID);
            builder.buildName(name);
            builder.buildDesc(desc);
            builder.buildTraffic(traffic);
            builder.buildDelay(delay);
            builder.buildPopHour(popHour);
            builder.buildConstruction(constr);

            // Gets the road from the builder
            std::unique_ptr<Road> road = builder.getRoad();

            // Saves the new road into the road list
            roadList.push_back(std::move(road));

            // Updates the road_database.txt file with the new road
            writeFile write;
            write.writeRoadFile("road_database.txt", roadList);

            // Lets the user know that the road has been added with a status message
            // Clears the status label in case something was in there
            ui->submit_status_2->clear();

            ui->submit_status_2->setText("Success: Road has been added!");
            ui->submit_status_2->setStyleSheet("QLabel { color: rgb(0, 255, 0); }");
            ui->submit_status_2->setAlignment(Qt::AlignCenter);

        // If the user inputted a road type Highway, then creates a new highway object and saves it into the roadList and updates file
        } else if(type == "Highway") {
            // Creates a new Local builder
            highwayBuilder builder;

            // Starts building the road
            builder.buildRoadID(roadID);
            builder.buildName(name);
            builder.buildDesc(desc);
            builder.buildTraffic(traffic);
            builder.buildDelay(delay);
            builder.buildPopHour(popHour);
            builder.buildConstruction(constr);

            // Gets the road from the builder
            std::unique_ptr<Road> road = builder.getRoad();

            // Saves the new road into the road list
            roadList.push_back(std::move(road));

            // Updates the road_database.txt file with the new road
            writeFile write;
            write.writeRoadFile("road_database.txt", roadList);

            // Lets the user know that the road has been added with a status message
            // Clears the status label in case something was in there
            ui->submit_status_2->clear();

            ui->submit_status_2->setText("Success: Road has been added!");
            ui->submit_status_2->setStyleSheet("QLabel { color: rgb(0, 255, 0); }");
            ui->submit_status_2->setAlignment(Qt::AlignCenter);
        }

    // If one of the checks above failed, lets the user know
    } else {
        // Clears the status label in case something was in there
        ui->submit_status_2->clear();

        ui->submit_status_2->setText("Error: Invalid value entered!");
        ui->submit_status_2->setStyleSheet("QLabel { color: rgb(255, 0, 0); }");
        ui->submit_status_2->setAlignment(Qt::AlignCenter);
    }

}


// PAGE 6: SEARCH ROADS PAGE
// When the user clicks the back button, takes them back to page 2 (main menu)
void MainWindow::on_back_to_menu_4_clicked()
{
    // Clears the searched roads text box
    ui->searched_roads->clear();
    // Clears the name search box if something was inputted
    ui->name_text_3->clear();

    // Back to the main menu
    ui->stackedWidget->setCurrentIndex(1);
}

// Buttons for the filters
// Method that displays all roads with "Light" traffic status in the text box
void MainWindow::on_traffic_light_clicked()
{
    // Clears the searched roads text box
    ui->searched_roads->clear();

    // For loop to cycle through the entire road list
    for(int i=0; i<roadList.size(); i++) {
        // Checks if the current index i of road list has a light traffic status
        if(roadList[i]->getTraffic() == "Light") {
            // If it does, then displays the road name and traffic status in the text box
            std::string temp = "Road Name: " + roadList[i]->getName() + "\nTraffic Status >> " + roadList[i]->getTraffic() + "\n";
            ui->searched_roads->append(QString::fromStdString(temp));
        }
    }
}

// Method that displays all roads with "Heavy" traffic status in the text box
void MainWindow::on_traffic_heavy_clicked()
{
    // Clears the searched roads text box
    ui->searched_roads->clear();

    // For loop to cycle through the entire road list
    for(int i=0; i<roadList.size(); i++) {
        // Checks if the current index i of road list has a heavy traffic status
        if(roadList[i]->getTraffic() == "Heavy") {
            // If it does, then displays the road name and traffic status in the text box
            std::string temp = "Road Name: " + roadList[i]->getName() + "\nTraffic Status >> " + roadList[i]->getTraffic() + "\n";
            ui->searched_roads->append(QString::fromStdString(temp));
        }
    }
}

// Method that displays all roads with a delay of 0 in the text box
void MainWindow::on_no_delay_clicked()
{
    // Clears the searched roads text box
    ui->searched_roads->clear();

    // For loop to cycle through the entire road list
    for(int i=0; i<roadList.size(); i++) {
        // Checks if the current index i of road list has 0 as the delay
        if(roadList[i]->getDelay() == 0) {
            // If it does, then displays the road name and delay in the text box
            std::string temp = "Road Name: " + roadList[i]->getName() + "\nCurrent Delay >> " + std::to_string(roadList[i]->getDelay()) + " minutes\n";
            ui->searched_roads->append(QString::fromStdString(temp));
        }
    }
}

// Method that displays all roads with a delay of greater than 0 in the text box
void MainWindow::on_has_delay_clicked()
{
    // Clears the searched roads text box
    ui->searched_roads->clear();

    // For loop to cycle through the entire road list
    for(int i=0; i<roadList.size(); i++) {
        // Checks if the current index i of road list has a delay greater than 0
        if(roadList[i]->getDelay() > 0) {
            // If it does, then displays the road name and delay in the text box
            std::string temp = "Road Name: " + roadList[i]->getName() + "\nCurrent Delay >> " + std::to_string(roadList[i]->getDelay()) + " minutes\n";
            ui->searched_roads->append(QString::fromStdString(temp));
        }
    }
}

// Method that displays all roads with no construction
void MainWindow::on_no_constr_clicked()
{
    // Clears the searched roads text box
    ui->searched_roads->clear();

    // For loop to cycle through the entire road list
    for(int i=0; i<roadList.size(); i++) {
        // Checks if the current index i of road list has false as construction status
        if(roadList[i]->getConstruction() == false) {
            // If it does, then displays the road name and construction status in the text box
            std::string temp = "Road Name: " + roadList[i]->getName() + "\nConstruction Status >> False\n";
            ui->searched_roads->append(QString::fromStdString(temp));
        }
    }
}

// Method that displays all roads with construction
void MainWindow::on_has_constr_clicked()
{
    // Clears the searched roads text box
    ui->searched_roads->clear();

    // For loop to cycle through the entire road list
    for(int i=0; i<roadList.size(); i++) {
        // Checks if the current index i of road list has true as construction status
        if(roadList[i]->getConstruction() == true) {
            // If it does, then displays the road name and construction status in the text box
            std::string temp = "Road Name: " + roadList[i]->getName() + "\nConstruction Status >> True\n";
            ui->searched_roads->append(QString::fromStdString(temp));
        }
    }
}

// Method that displays all roads with a popular hour in the morning (1-12)
void MainWindow::on_am_popHour_clicked()
{
    // Clears the searched roads text box
    ui->searched_roads->clear();

    // For loop to cycle through the entire road list
    for(int i=0; i<roadList.size(); i++) {
        // Checks if the current index i of road list has a popular hour from 1-12
        if(1 <= roadList[i]->getPopHour() && roadList[i]->getPopHour() <= 12) {
            // If it does, then displays the road name and most popular hour in the text box
            std::string temp = "Road Name: " + roadList[i]->getName() + "\nMost Popular Hour >> " + std::to_string(roadList[i]->getPopHour()) + ":00\n";
            ui->searched_roads->append(QString::fromStdString(temp));
        }
    }
}

// Method that displays all roads with a popular hour in the afternoon and night (13-23 and 0)
void MainWindow::on_pm_popHour_clicked()
{
    // Clears the searched roads text box
    ui->searched_roads->clear();

    // For loop to cycle through the entire road list
    for(int i=0; i<roadList.size(); i++) {
        // Checks if the current index i of road list has a popular hour from 13-23 or if it is 0
        if((13 <= roadList[i]->getPopHour() && roadList[i]->getPopHour() <= 23) || roadList[i]->getPopHour() == 0) {
            // If it does, then displays the road name and most popular hour in the text box
            std::string temp = "Road Name: " + roadList[i]->getName() + "\nMost Popular Hour >> " + std::to_string(roadList[i]->getPopHour()) + ":00\n";
            ui->searched_roads->append(QString::fromStdString(temp));
        }
    }
}

// Method that displays all roads with names containing the string that the user entered
void MainWindow::on_search_button_clicked()
{
    // Clears the searched roads text box
    ui->searched_roads->clear();

    // Takes the user input from the search text box
    std::string userInput = ui->name_text_3->toPlainText().toStdString();
    // Converts the user input to lowercase
    std::transform(userInput.begin(), userInput.end(), userInput.begin(), [](unsigned char c){ return std::tolower(c); });

    // For loop to cycle through the entire road list
    for(int i=0; i<roadList.size(); i++) {
        // For each road name, save into a temp array and convert road name to lowercase
        std::string tempName = roadList[i]->getName();
        std::transform(tempName.begin(), tempName.end(), tempName.begin(), [](unsigned char c){ return std::tolower(c); });

        // Compare the user input to the road name to see if the user input is a substring inside of the road name
        if (tempName.find(userInput) != std::string::npos) {
            // If user input is a substring of the road name, displays the road name
            std::string temp = "Road Name: " + roadList[i]->getName() + " contains your search term.\n";
            ui->searched_roads->append(QString::fromStdString(temp));
        }
    }
}

