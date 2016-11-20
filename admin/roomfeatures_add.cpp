#include "roomfeatures_add.h"
#include "ui_roomfeatures_add.h"

#include <QMessageBox>
#include <QString>
#include <QSqlDatabase>
#include <QCloseEvent>
#include <QSqlQuery>
#include <QDebug>

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

    QSqlDatabase db = QSqlDatabase::database();
    db.open();

    QSqlQuery query(db);

    QString string = QString("INSERT INTO jotel_features (name, description) VALUES ('%1', '%2');").arg(
                ui->featureLineEdit->text(), ui->descriptionLineEdit->text());
    query.prepare(string);
    query.exec(string);

    QMessageBox::information(this, "Feature added", QString("Feature '%1' added").arg(ui->featureLineEdit->text()), QMessageBox::Ok);
    this->destroy();
}
