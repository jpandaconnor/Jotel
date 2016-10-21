#include "databaseconnection.h"

#include <QString>
#include <QSqlDatabase>

DatabaseConnection::DatabaseConnection()
{
/*
 *
 * Database connection list
 *
 * QMYSQL - main
 *
 */
}

void DatabaseConnection::openConnection(QString address, QString dbname, QString username, QString password, int port) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(address);
    db.setDatabaseName(dbname);
    db.setUserName(username);
    db.setPassword(password);
    db.setPort(port);

    if(!db.isOpen()) {
        db.open();
    }
}

bool DatabaseConnection::isConnectableDatabase(QString address, QString dbname, QString username, QString password, int port) {
    bool succ = false;

    QSqlDatabase testdb = QSqlDatabase::addDatabase("QMYSQL", "query");
    testdb.setHostName(address);
    testdb.setDatabaseName(dbname);
    testdb.setUserName(username);
    testdb.setPassword(password);
    testdb.setPort(port);

    succ = testdb.open();

    testdb.close();

    return succ;
}

bool DatabaseConnection::checkConnection() {
    QSqlDatabase db = QSqlDatabase::database();
    return db.isOpen();
}
