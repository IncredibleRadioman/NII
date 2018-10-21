/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qterminal.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *connect;
    QLineEdit *address;
    QTerminal *console;
    QPushButton *micro;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *address_2;
    QPushButton *sound;
    QTextEdit *chat;
    QLineEdit *address_3;
    QLabel *label_3;
    QPushButton *refresh;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(484, 287);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/main.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        connect = new QPushButton(centralWidget);
        connect->setObjectName(QStringLiteral("connect"));
        connect->setGeometry(QRect(400, 0, 32, 32));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/disconnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        connect->setIcon(icon1);
        connect->setIconSize(QSize(24, 24));
        address = new QLineEdit(centralWidget);
        address->setObjectName(QStringLiteral("address"));
        address->setGeometry(QRect(220, 10, 91, 20));
        console = new QTerminal(centralWidget);
        console->setObjectName(QStringLiteral("console"));
        console->setGeometry(QRect(60, 200, 421, 31));
        micro = new QPushButton(centralWidget);
        micro->setObjectName(QStringLiteral("micro"));
        micro->setGeometry(QRect(0, 200, 32, 32));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/micro2.png"), QSize(), QIcon::Normal, QIcon::Off);
        micro->setIcon(icon2);
        micro->setIconSize(QSize(24, 24));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(140, 10, 81, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(315, 10, 47, 21));
        address_2 = new QLineEdit(centralWidget);
        address_2->setObjectName(QStringLiteral("address_2"));
        address_2->setGeometry(QRect(350, 10, 41, 20));
        sound = new QPushButton(centralWidget);
        sound->setObjectName(QStringLiteral("sound"));
        sound->setGeometry(QRect(30, 200, 32, 32));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/sound1.png"), QSize(), QIcon::Normal, QIcon::Off);
        sound->setIcon(icon3);
        sound->setIconSize(QSize(24, 24));
        chat = new QTextEdit(centralWidget);
        chat->setObjectName(QStringLiteral("chat"));
        chat->setGeometry(QRect(0, 40, 481, 151));
        address_3 = new QLineEdit(centralWidget);
        address_3->setObjectName(QStringLiteral("address_3"));
        address_3->setGeometry(QRect(35, 10, 101, 20));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(5, 10, 47, 21));
        refresh = new QPushButton(centralWidget);
        refresh->setObjectName(QStringLiteral("refresh"));
        refresh->setGeometry(QRect(440, 0, 32, 32));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        refresh->setIcon(icon4);
        refresh->setIconSize(QSize(24, 24));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 484, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MChat", nullptr));
        connect->setText(QString());
        address->setText(QApplication::translate("MainWindow", "172.25.33.63", nullptr));
        micro->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Server address:", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "PORT:", nullptr));
        address_2->setText(QApplication::translate("MainWindow", "5600", nullptr));
        sound->setText(QString());
        address_3->setText(QApplication::translate("MainWindow", "user", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "NICK:", nullptr));
        refresh->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
