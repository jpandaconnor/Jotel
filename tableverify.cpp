#include "tableverify.h"

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QString>
#include <QSqlError>
#include <QMessageBox>
#include <QApplication>
#include <QSqlRecord>

#include <QDebug>

TableVerify::TableVerify(QWidget *parent) : QWidget(parent)
{

}

void TableVerify::startChecking(QDialog* dialog) {
    checkTables();
}

void TableVerify::checkTables() {
    QSqlDatabase db = QSqlDatabase::database();

    if(db.open()) {
        if(!db.tables().contains("jotel_users")) {
            QSqlQuery query;
            if(!query.exec("CREATE TABLE jotel_users(username VARCHAR(200), pass VARCHAR(200), ugroup VARCHAR(200), perms VARCHAR(10));")) {
                QMessageBox::critical(this, "Error", QString("Database table '%1' creation failed. Error code: " + QString::number(query.lastError().number())).arg("jotel_users"), QMessageBox::Ok);
                QApplication::quit();
                return;
            }
        }
        
        if(!db.tables().contains("jotel_features")) {
            QSqlQuery query;
            if(!query.exec("CREATE TABLE jotel_features(id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, name TEXT, description TEXT);")) {
                QMessageBox::critical(this, "Error", QString("Database table '%1' creation failed. Error code: " + QString::number(query.lastError().number())).arg("jotel_features"), QMessageBox::Ok);
                QApplication::quit();
                return;
            }
        }

        if(!db.tables().contains("jotel_floors")) {
            QSqlQuery query;
            if(!query.exec("CREATE TABLE jotel_floors(id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, floor INT);")) {
                QMessageBox::critical(this, "Error", QString("Database table '%1' creation failed. Error code: " + QString::number(query.lastError().number())).arg("jotel_floors"), QMessageBox::Ok);
                QApplication::quit();
                return;
            }
        }

        if(!db.tables().contains("jotel_sections")) {
            QSqlQuery query;
            if(!query.exec("CREATE TABLE jotel_sections(id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, section INT);")) {
                QMessageBox::critical(this, "Error", QString("Database table '%1' creation failed. Error code: " + QString::number(query.lastError().number())).arg("jotel_sections"), QMessageBox::Ok);
                QApplication::quit();
                return;
            }
        }

        if(!db.tables().contains("jotel_rooms")) {
            QSqlQuery query;
            if(!query.exec("CREATE TABLE jotel_rooms(id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, no INT, floor INT, section INT, features VARCHAR(1024), room_type INT);")) {
                QMessageBox::critical(this, "Error", QString("Database table '%1' creation failed. Error code: " + QString::number(query.lastError().number())).arg("jotel_rooms"), QMessageBox::Ok);
                QApplication::quit();
                return;
            }
        }

        if(!db.tables().contains("jotel_roomtypes")) {
            qDebug() << "Not calling in here";
            QSqlQuery query;
            if(!query.exec("CREATE TABLE jotel_roomtypes(id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, name TEXT, description TEXT);")) {
                QMessageBox::critical(this, "Error", QString("Database table '%1' creation failed. Error code: " + QString::number(query.lastError().number())).arg("jotel_roomtypes"), QMessageBox::Ok);
                QApplication::quit();
                return;
            }
        }

        db.close();

        // checkAdmin();
    }
}

void TableVerify::checkAdmin() {
    QSqlDatabase db = QSqlDatabase::database();

    if(!db.isOpen()) {
        db.open();
    }

        QSqlQuery query;
        if(query.exec("SELECT username FROM jotel_users WHERE username = 'admin'")) {
            if(!query.next()) {
                QMessageBox::StandardButton adminsetup = QMessageBox::warning(this, "No admin account",
                                                                               tr("You must create a new admin account to continue"), QMessageBox::Ok);

                if(adminsetup == QMessageBox::Ok) {

                } else {
                    // Cancel
                }

                // No admin account - must be setup
            } else {
                // Else log in
            }
        }
}

