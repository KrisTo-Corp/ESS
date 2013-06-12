#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <cstdlib>
#include <iostream>
#include <QWebView>
#include <QUrl>
#include <QApplication>
#include "Simulator.h"

MainWindow::MainWindow(QWidget *parent, std::string inputfile, std::string inputfile_vehicles) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    city(inputfile, updatestream, inputfile_vehicles, false, true)
{
    ui->setupUi(this); 
    city.getMatrix()->printVehicles(city.o, city.getVehicles());
    ui->map->reload();
    updatestream.clear();
    updatestream.str("");
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_simulateButton_clicked()
{
    singleSimulate(&city);
    QMessageBox update_report;
    update_report.information(this, "Update Report", updatestream.str().c_str(), QMessageBox::Close);
    updatestream.clear();
    updatestream.str("");
    city.getMatrix()->printVehicles(city.o, city.getVehicles());
    ui->map->reload();
    updatestream.clear();
    updatestream.str("");
}

void MainWindow::on_setFireButton_clicked()
{
    int x = ui->xValue->value();
    int y = ui->yValue->value();
    bool valid = city.validFireCoordinates(x, y);
    if (!valid) {
        QMessageBox pop_up;
        pop_up.information(this, "Error!", "Invalid coordinates.", QMessageBox::Close);
    }
    else {
        city.setFire(x, y);
        QMessageBox pop_up;
        pop_up.information(this, "Succes!", "The fire was succesfully set.", QMessageBox::Close);
    }
}

void MainWindow::on_startRobberyButton_clicked()
{
    int x = ui->xValue->value();
    int y = ui->yValue->value();
    bool valid = city.validRobberyCoordinates(x, y);
    if (!valid) {
        QMessageBox pop_up;
        pop_up.information(this, "Error!", "Invalid coordinates.", QMessageBox::Close);
    }
    else {
        city.robStore(x, y);
        QMessageBox pop_up;
        pop_up.information(this, "Succes!", "The store is now being robbed.", QMessageBox::Close);
    }
}

void MainWindow::on_simulateButton_clicked(bool b)
{

}
