#-------------------------------------------------
#
# Project created by QtCreator 2011-10-13T22:35:09
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab2_client
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    myclient.cpp \
    ../Lab2_server/myserver.cpp \
    myserver.cpp

HEADERS  += dialog.h \
    myclient.h \
    ../Lab2_server/myserver.h \
    myserver.h


FORMS    += dialog.ui



