#include <QtGui/QApplication>
#include "mainwindow.h"
#include <string>
#include <sstream>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc == 2){
        std::string inputfile = argv[1];
        QApplication a(argc, argv);
        MainWindow w(0, inputfile);
        w.setWindowTitle("Emergency Services Simulator");
        w.show();

        return a.exec();

    }
    else if (argc == 3){
        std::string inputfile = argv[1];
        std::string inputfile_vehicles = argv[2];
        QApplication a(argc, argv);
        MainWindow w(0, inputfile, inputfile_vehicles);
        w.setWindowTitle("Emergency Services Simulator");
        w.show();

        return a.exec();
    }
    else {
        std::cerr << "Usage: ./exec [XML FILE CITY] [XML FILE VEHICLES]*\t\t*optional" << std::endl;
    }
}
