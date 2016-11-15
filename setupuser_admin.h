#ifndef SETUPUSER_ADMIN_H
#define SETUPUSER_ADMIN_H

#include <QDialog>

namespace Ui {
class setupuser_admin;
}

class setupuser_admin : public QDialog
{
    Q_OBJECT

public:
    explicit setupuser_admin(QWidget *parent = 0);
    ~setupuser_admin();

private:
    Ui::setupuser_admin *ui;
};

#endif // SETUPUSER_ADMIN_H
