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

    // Opening room features stuff here

public slots:
     void openRoomFeatures_Add();
     void openRoomFeatures_Edit();

private slots:
     void on_actionRoom_Editor_triggered();

private:
    Ui::InitialWindow *ui;

    void loadSettings();

private:
    QString dir_setting_database;
    QSettings* file_setting_database;
};

#endif // INITIALWINDOW_H
