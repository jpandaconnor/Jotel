#include "setupuser_admin.h"
#include "ui_setupuser_admin.h"

setupuser_admin::setupuser_admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setupuser_admin)
{
    ui->setupUi(this);
}

setupuser_admin::~setupuser_admin()
{
    delete ui;
}
