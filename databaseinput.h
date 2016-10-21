#ifndef DATABASEINPUT_H
#define DATABASEINPUT_H

#include <QDialog>

namespace Ui {
class DatabaseInput;
}

class DatabaseInput : public QDialog
{
    Q_OBJECT

public:
    explicit DatabaseInput(QWidget *parent = 0);
    ~DatabaseInput();

private:
    Ui::DatabaseInput *ui;

private:
    void closeEvent(QCloseEvent* event);
    void accept();
    void checkInput();
    void greyIn();
    void greyOut();
};

#endif // DATABASEINPUT_H
