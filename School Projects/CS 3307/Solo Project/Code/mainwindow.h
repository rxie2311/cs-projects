#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt Libraries
#include <QMainWindow>

// C++ Libraries
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>

// Other Classes
#include "qlistwidget.h"
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


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Helper Methods
    void generateList();
    void fillListWidget();
    void linkDisplay();
    std::vector<int> splitString(std::string& str);

private slots:
    // PAGE 1: LOGIN PAGE
    void on_log_in_clicked();

    // PAGE 2: MAIN MENU
    // Side buttons
    void on_log_out_clicked();
    void on_watchlist_clicked();
    void on_search_clicked();
    // Road List Widget
    void on_road_list_itemClicked(QListWidgetItem *item);
    // Watchlist Add/Remove buttons
    void on_add_watchlist_clicked();
    void on_remove_watchlist_clicked();
    // Employee and Manager Perms
    void on_edit_road_clicked();
    void on_add_road_clicked();

    // PAGE 3: WATCHLIST
    void on_back_to_menu_clicked();

    // PAGE 4: EDIT ROAD ATTRIBUTES PAGE
    void on_back_to_menu_2_clicked();
    void on_submit_clicked();

    // PAGE 5: ADD ROAD PAGE
    void on_back_to_menu_3_clicked();
    void on_submit_2_clicked();

    // PAGE 6: SEARCH ROADS PAGE
    void on_back_to_menu_4_clicked();
    // Filters
    // Traffic filters
    void on_traffic_light_clicked();
    void on_traffic_heavy_clicked();
    // Delay filters
    void on_no_delay_clicked();
    void on_has_delay_clicked();
    // Construction filters
    void on_no_constr_clicked();
    void on_has_constr_clicked();
    // Popular Hour filters
    void on_am_popHour_clicked();
    void on_pm_popHour_clicked();
    // Search for road by name
    void on_search_button_clicked();

private:
    Ui::MainWindow *ui;

    // Instance variables
    // Road list that saves all the roads from the database file for referencing
    std::vector<std::unique_ptr<Road>> roadList;
    // User list that saves all the users from the database file for referencing
    std::vector<std::unique_ptr<User>> userList;
    // Current user that is logged in
    std::unique_ptr<User> currUser;
    // Road Watch observer subject to be used when a road attribute is updated
    roadWatcher roadWatch;
    // Display object to create an update message
    Display display;
};

#endif // MAINWINDOW_H
