/********************************************************************************
** Form generated from reading UI file 'vclientwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VCLIENTWINDOW_H
#define UI_VCLIENTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VClientWindow
{
public:
    QAction *actionExit;
    QAction *menuItemExit;
    QAction *actionScreen_Sharing;
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLineEdit *hostTextField;
    QLabel *label_2;
    QSpinBox *portSpin;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *connectButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPlainTextEdit *console;
    QTextEdit *inputTextField;
    QProgressBar *progressBar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuFile_2;
    QMenu *menuServer;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *VClientWindow)
    {
        if (VClientWindow->objectName().isEmpty())
            VClientWindow->setObjectName(QStringLiteral("VClientWindow"));
        VClientWindow->resize(541, 578);
        actionExit = new QAction(VClientWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        menuItemExit = new QAction(VClientWindow);
        menuItemExit->setObjectName(QStringLiteral("menuItemExit"));
        actionScreen_Sharing = new QAction(VClientWindow);
        actionScreen_Sharing->setObjectName(QStringLiteral("actionScreen_Sharing"));
        centralWidget = new QWidget(VClientWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 541, 41));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 2, 1, 1, 1);

        hostTextField = new QLineEdit(gridLayoutWidget);
        hostTextField->setObjectName(QStringLiteral("hostTextField"));

        gridLayout_2->addWidget(hostTextField, 2, 3, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 2, 4, 1, 1);

        portSpin = new QSpinBox(gridLayoutWidget);
        portSpin->setObjectName(QStringLiteral("portSpin"));
        portSpin->setMaximum(65536);
        portSpin->setValue(2000);

        gridLayout_2->addWidget(portSpin, 2, 6, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 2, 5, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 2, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 2, 7, 1, 1);

        connectButton = new QPushButton(gridLayoutWidget);
        connectButton->setObjectName(QStringLiteral("connectButton"));

        gridLayout_2->addWidget(connectButton, 2, 8, 1, 1);

        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(0, 40, 541, 231));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 539, 229));
        console = new QPlainTextEdit(scrollAreaWidgetContents);
        console->setObjectName(QStringLiteral("console"));
        console->setEnabled(true);
        console->setGeometry(QRect(0, 0, 531, 231));
        console->setMaximumSize(QSize(531, 16777215));
        console->setReadOnly(true);
        scrollArea->setWidget(scrollAreaWidgetContents);
        inputTextField = new QTextEdit(centralWidget);
        inputTextField->setObjectName(QStringLiteral("inputTextField"));
        inputTextField->setGeometry(QRect(3, 277, 531, 241));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(200, 400, 118, 23));
        progressBar->setMaximumSize(QSize(16777211, 16777215));
        progressBar->setValue(24);
        VClientWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(VClientWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 541, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuFile_2 = new QMenu(menuBar);
        menuFile_2->setObjectName(QStringLiteral("menuFile_2"));
        menuServer = new QMenu(menuBar);
        menuServer->setObjectName(QStringLiteral("menuServer"));
        VClientWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(VClientWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        VClientWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(VClientWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        VClientWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuFile_2->menuAction());
        menuBar->addAction(menuServer->menuAction());
        menuFile->addAction(actionExit);
        menuFile_2->addAction(menuItemExit);
        menuServer->addAction(actionScreen_Sharing);

        retranslateUi(VClientWindow);
        QObject::connect(menuItemExit, SIGNAL(activated()), VClientWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(VClientWindow);
    } // setupUi

    void retranslateUi(QMainWindow *VClientWindow)
    {
        VClientWindow->setWindowTitle(QApplication::translate("VClientWindow", "VClientWindow", nullptr));
        actionExit->setText(QApplication::translate("VClientWindow", "Exit", nullptr));
        menuItemExit->setText(QApplication::translate("VClientWindow", "Exit", nullptr));
        actionScreen_Sharing->setText(QApplication::translate("VClientWindow", "Screen Sharing", nullptr));
        label->setText(QApplication::translate("VClientWindow", "Host", nullptr));
        hostTextField->setText(QApplication::translate("VClientWindow", "localhost", nullptr));
        label_2->setText(QApplication::translate("VClientWindow", "Port", nullptr));
        connectButton->setText(QApplication::translate("VClientWindow", "Connect", nullptr));
        menuFile->setTitle(QApplication::translate("VClientWindow", "File", nullptr));
        menuFile_2->setTitle(QApplication::translate("VClientWindow", "File", nullptr));
        menuServer->setTitle(QApplication::translate("VClientWindow", "Server", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VClientWindow: public Ui_VClientWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VCLIENTWINDOW_H
