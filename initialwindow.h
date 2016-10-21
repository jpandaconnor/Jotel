#ifndef INITIALWINDOW_H
#define INITIALWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QSettings>

namespace Ui {
class InitialWindow;
}

class InitialWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InitialWindow(QWidget *parent = 0);
    ~InitialWindow();

private:
    Ui::InitialWindow *ui;

    void loadSettings();

private:
    QString dir_setting_database;
    QSettings* file_setting_database;
};

#endif // INITIALWINDOW_H
