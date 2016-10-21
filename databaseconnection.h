#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QString>

class DatabaseConnection
{
public:
    DatabaseConnection();

    bool checkConnection();
    bool isConnectableDatabase(QString address, QString dbname, QString username, QString password, int port);

    void openConnection(QString address, QString dbname, QString username, QString password, int port);

    QString getDatabaseError();
private:
};

#endif // DATABASECONNECTION_H
