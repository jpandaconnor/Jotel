#ifndef CREATE_LOGIN_ROOT_H
#define CREATE_LOGIN_ROOT_H

#include <QDialog>

namespace Ui {
class Create_Login_root;
}

class Create_Login_root : public QDialog
{
    Q_OBJECT

public:
    explicit Create_Login_root(QWidget *parent = 0);
    ~Create_Login_root();

private:
    Ui::Create_Login_root *ui;

    void closeEvent(QCloseEvent* event);
    void accept();
    void reject();
    void checkInput();
};

#endif // CREATE_LOGIN_ROOT_H
