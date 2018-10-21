/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout;
    QListWidget *lwLog;
    QListWidget *lwUsers;
    QPlainTextEdit *pteMessage;
    QVBoxLayout *verticalLayout;
    QLineEdit *leHost;
    QSpinBox *sbPort;
    QLineEdit *leName;
    QPushButton *pbConnect;
    QPushButton *pbDisconnect;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pbSend;
    QCheckBox *cbToAll;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(529, 387);
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lwLog = new QListWidget(Dialog);
        lwLog->setObjectName(QStringLiteral("lwLog"));

        gridLayout->addWidget(lwLog, 0, 0, 1, 1);

        lwUsers = new QListWidget(Dialog);
        lwUsers->setObjectName(QStringLiteral("lwUsers"));
        lwUsers->setSelectionMode(QAbstractItemView::MultiSelection);
        lwUsers->setSortingEnabled(true);

        gridLayout->addWidget(lwUsers, 0, 1, 1, 5);

        pteMessage = new QPlainTextEdit(Dialog);
        pteMessage->setObjectName(QStringLiteral("pteMessage"));

        gridLayout->addWidget(pteMessage, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        leHost = new QLineEdit(Dialog);
        leHost->setObjectName(QStringLiteral("leHost"));

        verticalLayout->addWidget(leHost);

        sbPort = new QSpinBox(Dialog);
        sbPort->setObjectName(QStringLiteral("sbPort"));
        sbPort->setMaximum(65536);
        sbPort->setValue(1234);

        verticalLayout->addWidget(sbPort);

        leName = new QLineEdit(Dialog);
        leName->setObjectName(QStringLiteral("leName"));

        verticalLayout->addWidget(leName);

        pbConnect = new QPushButton(Dialog);
        pbConnect->setObjectName(QStringLiteral("pbConnect"));

        verticalLayout->addWidget(pbConnect);

        pbDisconnect = new QPushButton(Dialog);
        pbDisconnect->setObjectName(QStringLiteral("pbDisconnect"));
        pbDisconnect->setEnabled(false);

        verticalLayout->addWidget(pbDisconnect);


        gridLayout->addLayout(verticalLayout, 1, 4, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        pbSend = new QPushButton(Dialog);
        pbSend->setObjectName(QStringLiteral("pbSend"));
        pbSend->setEnabled(false);

        verticalLayout_2->addWidget(pbSend);

        cbToAll = new QCheckBox(Dialog);
        cbToAll->setObjectName(QStringLiteral("cbToAll"));
        cbToAll->setChecked(true);

        verticalLayout_2->addWidget(cbToAll);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout_2, 1, 3, 1, 1);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Lab2 client", nullptr));
        leHost->setText(QApplication::translate("Dialog", "127.0.0.1", nullptr));
        leName->setText(QApplication::translate("Dialog", "MyName", nullptr));
        pbConnect->setText(QApplication::translate("Dialog", "Connect", nullptr));
        pbDisconnect->setText(QApplication::translate("Dialog", "Disconnect", nullptr));
        pbSend->setText(QApplication::translate("Dialog", "Send", nullptr));
        cbToAll->setText(QApplication::translate("Dialog", "To ALL", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
