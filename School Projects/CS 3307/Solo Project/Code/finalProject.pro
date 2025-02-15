QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    loadFile.cpp \
    main.cpp \
    mainwindow.cpp \
    observer.cpp \
    road.cpp \
    roadBuilder.cpp \
    roadFactory.cpp \
    roadWatcher.cpp \
    user.cpp \
    userFactory.cpp \
    writeFile.cpp

HEADERS += \
    loadFile.h \
    mainwindow.h \
    observer.h \
    road.h \
    roadBuilder.h \
    roadFactory.h \
    roadWatcher.h \
    user.h \
    userFactory.h \
    writeFile.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
