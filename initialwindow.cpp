#include "initialwindow.h"
#include "ui_initialwindow.h"
#include "databaseinput.h"

#include "admin/roomfeatures_add.h"
#include "admin/roomfeatures_edit.h"

#include "admin/room_editor.h"

#include <QApplication>
#include <QSettings>

#include <QSqlDatabase>
#include <QSqlQuery>

#include <QMessageBox>

#include <QDebug>

/*
 *
 * This window will be the starting window that
 * determines whether the database has been setup
 * and if to log in or not
 *
 * 1) Check database is in settings
 * If not prompt screen
 * Else retrieve encrypted settings and connect
 *
 * Determine next screen from there
 *
 */

InitialWindow::InitialWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InitialWindow)
{
    ui->setupUi(this);

    dir_setting_database = QApplication::applicationDirPath().left(1) + ":/databasesettings.ini";
    file_setting_database = new QSettings(dir_setting_database, QSettings::NativeFormat);

    if(!file_setting_database->contains("dbname")) {
        DatabaseInput* dbinput = new DatabaseInput();
        dbinput->setModal(true);
        dbinput->show();
    } else {
        // Get all the information here and do stuf
    }

    qDebug() << "Inaudible scremaing";
}

InitialWindow::~InitialWindow()
{
    delete ui;
    delete file_setting_database;
}

void InitialWindow::openRoomFeatures_Add() {
    RoomFeatures_Add* rma = new RoomFeatures_Add();
    rma->open();
}

void InitialWindow::openRoomFeatures_Edit() {
    RoomFeatures_Edit* rme = new RoomFeatures_Edit();
    rme->open();
}

void InitialWindow::on_actionRoom_Editor_triggered()
{
    Room_Editor* re = new Room_Editor();
    re->open();
}
