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
                QMessageBox::critical(this, "Error", "Database table creation failed. Error code: " + QString::number(query.lastError().number()), QMessageBox::Ok);
                QApplication::quit();
                return;
            } else {
                db.close();
            }
        }

        checkAdmin();
    }
}

void TableVerify::checkAdmin() {
    QSqlDatabase db = QSqlDatabase::database();

    if(db.open()) {
        QSqlQuery query;
        if(query.exec("SELECT username FROM jotel_users WHERE username = 'admin'")) {
            if(!query.next()) {
                QMessageBox::StandardButton adminsetup = QMessageBox::question(this, "Enter admin setup",
                                                                               tr("No admin account found! Setup admin account now?"), QMessageBox::Yes | QMessageBox::No);

                if(adminsetup == QMessageBox::Yes) {

                } else {
                    // Cancel
                }

                // No admin account - must be setup
            } else {
                // Else log in
            }
        }
    }
}

