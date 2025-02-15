CS3307 Final Project: Road Watch Program
Author: Raymond Xie
Student Number: 251275727
Email: rxie46@uwo.ca
-----------------------------------------------

CONSIDERATIONS - IMPORTANT
-----------------------------------------------
This project was coded using Qt Creator and C++. It was compiled on Windows 11.

There are two text files placed inside of the build folder (same directory as the MakeFile) named "accounts.txt" and "road_database.txt" that are necessary for my program to run, so make sure to also copy those when moving the code from GitHub to your own device.

Ensure the 2 .txt files are placed in the same directory as the Makefile. The program assumes that the build folder is the default working directory and will search the build folder for those two .txt files. If they are not placed in the same directory as the Makefile, the files will fail to open.

Ensure that you are running the program with the UI on PAGE 1 (login page) of the Stacked Widget, otherwise the program will not run correctly.


INSTRUCTIONS
-----------------------------------------------
To use my program, first, you must log in. 3 test accounts of each account type (Customer, Employee, Manager) have been set up inside of the "accounts.txt" file inside of the build folder and you may use those to log in.

Once you log in, you can click on each road in the "All Roads" text box on the left. When clicked on, the road details will be displayed on the textbox on the right.

You can add/remove to the watchlist when you click on a road and click on add to watchlist and remove from watchlist at the bottom of the left textbox.

You can edit road attributes (namely delay, most popular hour, traffic status and construction status) if you are logged onto the employee or manager level account, the customer level account will deny access to that menu.

You can add a road via the program into the road_database.txt file if you are logged onto the manager level account, the employee and customer level account will deny access to that menu.

The watchlist report section will detect for any changes in roads on the current user's watchlist if they have been edited via the "Edit Roads" menu. Editing the roads file directly will not trigger the observer, therefore the best way of testing the observer is to use the Employee or Manager level accounts to edit the attributes of a road in that account's watchlist.

The search button will take you to the search menu, where you can filter roads by attributes (such as light traffic vs heavy traffic, no construction vs has construction, ect) as well as search for roads by name. Typing in a string in the text box and clicking submit will search all road names in the database and output the names that contain your inputted string within them.

You may log in to a different account by clicking the log out button on the top left of the main menu. Clicking that button will take you back to the log in screen.


FILE FORMAT
-----------------------------------------------
road_database.txt is the text file used to store all of the Road objects that will be made into objects in my program.
Each road stored in the file will have the following format:

Road name (String)
Road description (String)
Road traffic (String: Light, Heavy)
Road type (String: Local, Highway)
Delay on the road (int: in minutes)
Most popular hour of the road (int: 0-23, 24 hour time)
Construction on the road (True/False)
Road ID (int)


accounts.txt is the text file used to store all account information for logging in.
All account information stored in the file will have the following format:

Username (String)
Password (String)
Account type (String: User, Employee, Manager)
Road IDs separated by commas for a watchlist


It is crucial that the following formats in each database file is not changed, else the program will read the file incorrectly.