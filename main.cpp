#include "initialwindow.h"
#include <QApplication>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InitialWindow w;
    w.show();

    qDebug() << "Opened";
    qDebug() << "Valid?";

    return a.exec();
}
