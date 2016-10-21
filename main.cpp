#include "initialwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InitialWindow w;
    w.show();

    return a.exec();
}

