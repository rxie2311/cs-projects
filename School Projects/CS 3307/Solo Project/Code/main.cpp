#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    // Calls on generateList to generate lists
    w.generateList();
    // Calls on linkDisplay to link the display to the subject
    w.linkDisplay();

    return a.exec();
}
