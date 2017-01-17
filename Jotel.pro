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
    passwordcrypto.cpp \
    admin/roomfeatures_add.cpp \
    admin/roomfeatures_edit.cpp \
    admin/room_editor.cpp \
    sql/csqlquerymodel.cpp

HEADERS  += initialwindow.h \
    databaseinput.h \
    databaseconnection.h \
    tableverify.h \
    create_login_root.h \
    passwordcrypto.h \
    admin/roomfeatures_add.h \
    admin/roomfeatures_edit.h \
    admin/room_editor.h \
    sql/csqlquerymodel.h

FORMS    += initialwindow.ui \
    databaseinput.ui \
    create_login_root.ui \
    admin/roomfeatures_add.ui \
    admin/roomfeatures_edit.ui \
    admin/room_editor.ui
