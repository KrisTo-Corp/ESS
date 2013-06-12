#-------------------------------------------------
#
# Project created by QtCreator 2013-06-12T10:24:22
#
#-------------------------------------------------

QT       += core gui

TARGET = ESS-GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xmlparser.cpp \
    Vehicles.cpp \
    tinyxmlparser.cpp \
    tinyxmlerror.cpp \
    tinyxml.cpp \
    tinystr.cpp \
    Structures.cpp \
    Simulator.cpp \
    Roads.cpp \
    OutputObject.cpp \
    Matrix.cpp \
    helpers.cpp \
    Coordinate.cpp \
    CityObjects.cpp \
    City.cpp \
    Casualty.cpp

HEADERS  += mainwindow.h \
    xmlparser.h \
    Vehicles.h \
    tinyxml.h \
    tinystr.h \
    Structures.h \
    Simulator.h \
    Roads.h \
    OutputObject.h \
    Matrix.h \
    helpers.h \
    DesignByContract.h \
    Coordinate.h \
    CityObjects.h \
    City.h \
    Casualty.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    mainwindow.ui.autosave \
    ESS-GUI.pro.user
