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

