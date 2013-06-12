/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Jun 12 15:16:08 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTextBrowser *map;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *xValue;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *yValue;
    QPushButton *setFireButton;
    QPushButton *startRobberyButton;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *simulateButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(2093, 732);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        map = new QTextBrowser(centralWidget);
        map->setObjectName(QString::fromUtf8("map"));
        map->setGeometry(QRect(10, 0, 2071, 511));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(660, 530, 740, 134));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(21, 17));

        horizontalLayout->addWidget(label);

        xValue = new QSpinBox(widget);
        xValue->setObjectName(QString::fromUtf8("xValue"));
        xValue->setMinimumSize(QSize(91, 27));
        xValue->setMaximumSize(QSize(91, 27));

        horizontalLayout->addWidget(xValue);


        horizontalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(21, 17));

        horizontalLayout_2->addWidget(label_2);

        yValue = new QSpinBox(widget);
        yValue->setObjectName(QString::fromUtf8("yValue"));
        yValue->setMinimumSize(QSize(91, 27));
        yValue->setMaximumSize(QSize(91, 27));

        horizontalLayout_2->addWidget(yValue);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        horizontalLayout_4->addLayout(horizontalLayout_3);

        setFireButton = new QPushButton(widget);
        setFireButton->setObjectName(QString::fromUtf8("setFireButton"));
        setFireButton->setMinimumSize(QSize(241, 51));

        horizontalLayout_4->addWidget(setFireButton);

        startRobberyButton = new QPushButton(widget);
        startRobberyButton->setObjectName(QString::fromUtf8("startRobberyButton"));
        startRobberyButton->setMinimumSize(QSize(241, 51));

        horizontalLayout_4->addWidget(startRobberyButton);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        simulateButton = new QPushButton(widget);
        simulateButton->setObjectName(QString::fromUtf8("simulateButton"));
        simulateButton->setMinimumSize(QSize(171, 71));

        horizontalLayout_5->addWidget(simulateButton);


        verticalLayout->addLayout(horizontalLayout_5);

        MainWindow->setCentralWidget(centralWidget);
        xValue->raise();
        label->raise();
        simulateButton->raise();
        map->raise();
        simulateButton->raise();
        simulateButton->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 2093, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "X : ", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Y :", 0, QApplication::UnicodeUTF8));
        setFireButton->setText(QApplication::translate("MainWindow", "Set Fire !", 0, QApplication::UnicodeUTF8));
        startRobberyButton->setText(QApplication::translate("MainWindow", "Start Robbery !", 0, QApplication::UnicodeUTF8));
        simulateButton->setText(QApplication::translate("MainWindow", "Simulate", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
