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
    tableverify.cpp \
    create_login_root.cpp \
    passwordcrypto.cpp

HEADERS  += initialwindow.h \
    databaseinput.h \
    databaseconnection.h \
    tableverify.h \
    create_login_root.h \
    passwordcrypto.h

FORMS    += initialwindow.ui \
    databaseinput.ui \
    create_login_root.ui
