#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <sstream>
#include "City.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0, std::string inputfile = "empty", std::string inputfile_vechicles = "empty");
    ~MainWindow();
    
private slots:
    void on_simulateButton_clicked();

    void on_setFireButton_clicked();

    void on_startRobberyButton_clicked();

    void on_simulateButton_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    std::stringstream updatestream;
    City city;
};

#endif // MAINWINDOW_H
