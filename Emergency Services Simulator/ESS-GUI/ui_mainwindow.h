/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Jun 12 17:57:48 2013
**      by: Qt User Interface Compiler version 4.8.3
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
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
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
    QWebView *map;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(789, 768);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 570, 740, 134));
        verticalLayout = new QVBoxLayout(layoutWidget);
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
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(21, 17));

        horizontalLayout->addWidget(label);

        xValue = new QSpinBox(layoutWidget);
        xValue->setObjectName(QString::fromUtf8("xValue"));
        xValue->setMinimumSize(QSize(91, 27));
        xValue->setMaximumSize(QSize(91, 27));

        horizontalLayout->addWidget(xValue);


        horizontalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(21, 17));

        horizontalLayout_2->addWidget(label_2);

        yValue = new QSpinBox(layoutWidget);
        yValue->setObjectName(QString::fromUtf8("yValue"));
        yValue->setMinimumSize(QSize(91, 27));
        yValue->setMaximumSize(QSize(91, 27));

        horizontalLayout_2->addWidget(yValue);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        horizontalLayout_4->addLayout(horizontalLayout_3);

        setFireButton = new QPushButton(layoutWidget);
        setFireButton->setObjectName(QString::fromUtf8("setFireButton"));
        setFireButton->setMinimumSize(QSize(241, 51));

        horizontalLayout_4->addWidget(setFireButton);

        startRobberyButton = new QPushButton(layoutWidget);
        startRobberyButton->setObjectName(QString::fromUtf8("startRobberyButton"));
        startRobberyButton->setMinimumSize(QSize(241, 51));

        horizontalLayout_4->addWidget(startRobberyButton);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        simulateButton = new QPushButton(layoutWidget);
        simulateButton->setObjectName(QString::fromUtf8("simulateButton"));
        simulateButton->setMinimumSize(QSize(171, 71));

        horizontalLayout_5->addWidget(simulateButton);


        verticalLayout->addLayout(horizontalLayout_5);

        map = new QWebView(centralWidget);
        map->setObjectName(QString::fromUtf8("map"));
        map->setGeometry(QRect(30, -10, 721, 571));
        map->setAutoFillBackground(false);
        map->setUrl(QUrl(QString::fromUtf8("file:///home/owner/git/ESS5/Emergency Services Simulator/ESS-GUI/map.html")));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 789, 25));
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
