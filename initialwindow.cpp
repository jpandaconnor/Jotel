#include "initialwindow.h"
#include "ui_initialwindow.h"
#include "databaseinput.h"

#include <QApplication>
#include <QSettings>

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