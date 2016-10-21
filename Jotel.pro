#-------------------------------------------------
#
# Project created by QtCreator 2016-10-19T23:40:14
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Jotel
TEMPLATE = app


SOURCES += main.cpp\
        initialwindow.cpp \
    databaseinput.cpp \
    databaseconnection.cpp \
    tableverify.cpp

HEADERS  += initialwindow.h \
    databaseinput.h \
    databaseconnection.h \
    tableverify.h

FORMS    += initialwindow.ui \
    databaseinput.ui
