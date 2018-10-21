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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QListWidget *lwLog;
    QListWidget *lwUsers;
    QHBoxLayout *horizontalLayout;
    QPushButton *pbStartStop;
    QLineEdit *leHost;
    QLineEdit *lePort;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbSend;
    QCheckBox *cbToAll;
    QHBoxLayout *horizontalLayout_2;
    QPlainTextEdit *pteMessage;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(549, 320);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        splitter = new QSplitter(Dialog);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        lwLog = new QListWidget(splitter);
        lwLog->setObjectName(QStringLiteral("lwLog"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lwLog->sizePolicy().hasHeightForWidth());
        lwLog->setSizePolicy(sizePolicy);
        lwLog->setSelectionRectVisible(false);
        splitter->addWidget(lwLog);
        lwUsers = new QListWidget(splitter);
        lwUsers->setObjectName(QStringLiteral("lwUsers"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lwUsers->sizePolicy().hasHeightForWidth());
        lwUsers->setSizePolicy(sizePolicy1);
        lwUsers->setSelectionMode(QAbstractItemView::MultiSelection);
        lwUsers->setSortingEnabled(true);
        splitter->addWidget(lwUsers);

        verticalLayout->addWidget(splitter);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pbStartStop = new QPushButton(Dialog);
        pbStartStop->setObjectName(QStringLiteral("pbStartStop"));
        pbStartStop->setCheckable(true);
        pbStartStop->setChecked(false);

        horizontalLayout->addWidget(pbStartStop);

        leHost = new QLineEdit(Dialog);
        leHost->setObjectName(QStringLiteral("leHost"));

        horizontalLayout->addWidget(leHost);

        lePort = new QLineEdit(Dialog);
        lePort->setObjectName(QStringLiteral("lePort"));

        horizontalLayout->addWidget(lePort);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbSend = new QPushButton(Dialog);
        pbSend->setObjectName(QStringLiteral("pbSend"));

        horizontalLayout->addWidget(pbSend);

        cbToAll = new QCheckBox(Dialog);
        cbToAll->setObjectName(QStringLiteral("cbToAll"));
        cbToAll->setChecked(true);
        cbToAll->setTristate(false);

        horizontalLayout->addWidget(cbToAll);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pteMessage = new QPlainTextEdit(Dialog);
        pteMessage->setObjectName(QStringLiteral("pteMessage"));

        horizontalLayout_2->addWidget(pteMessage);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Lab2 server", nullptr));
        pbStartStop->setText(QApplication::translate("Dialog", "Stop server", nullptr));
        leHost->setText(QApplication::translate("Dialog", "127.0.0.1", nullptr));
        lePort->setText(QApplication::translate("Dialog", "1234", nullptr));
        pbSend->setText(QApplication::translate("Dialog", "Send To All", nullptr));
        cbToAll->setText(QApplication::translate("Dialog", "To All", nullptr));
#ifndef QT_NO_SHORTCUT
        cbToAll->setShortcut(QString());
#endif // QT_NO_SHORTCUT
        pteMessage->setPlainText(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
