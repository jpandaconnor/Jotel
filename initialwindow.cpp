#include "initialwindow.h"
#include "ui_initialwindow.h"
#include "databaseinput.h"

#include "roomfeatures/roomfeatures_add.h"
#include "roomfeatures/roomfeatures_edit.h"

#include <QApplication>
#include <QSettings>

#include <QSqlDatabase>
#include <QSqlQuery>

#include <QMessageBox>

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
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    query.exec("SELECT name FROM jotel_features");

    if(!query.next()) {
        QMessageBox::warning(this, "No room features", tr("There are no room features"), QMessageBox::Ok);
        return;
    }

    RoomFeatures_Edit* rme = new RoomFeatures_Edit();
    rme->open();
}
