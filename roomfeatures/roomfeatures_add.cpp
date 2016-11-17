#include "roomfeatures_add.h"
#include "ui_roomfeatures_add.h"

#include <QMessageBox>
#include <QString>

RoomFeatures_Add::RoomFeatures_Add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoomFeatures_Add)
{
    ui->setupUi(this);
}

RoomFeatures_Add::~RoomFeatures_Add()
{
    delete ui;
}

void RoomFeatures_Add::accept() {
    checkInput();
}

void RoomFeatures_Add::reject() {
    this->close();
}

void RoomFeatures_Add::checkInput() {
    if(ui->featureLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Error", tr("Feature name cannot be empty"), QMessageBox::Ok);
        return;
    }

    QString fname = ui->featureLineEdit->text();

    QMessageBox::information(this, "Feature added", QString("Feature '%1' added").arg(fname), QMessageBox::Ok);
    this->destroy();
}
