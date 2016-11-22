#include "roomfeatures_edit.h"
#include "ui_roomfeatures_edit.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QMessageBox>
#include <QListWidgetItem>

const QListWidgetItem* lastitem = NULL;

RoomFeatures_Edit::RoomFeatures_Edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoomFeatures_Edit)
{
    ui->setupUi(this);

    ui->deleteButton->setEnabled(false);

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    query.exec("SELECT * FROM jotel_features");

    while(query.next()) {
        QListWidgetItem* nitem = new QListWidgetItem;
        QVariant qv_id(query.value(0).toInt());
        QVariant qv_des(query.value(2).toString());

        nitem->setData(Qt::UserRole, qv_id);
        nitem->setData(Qt::UserRole + 1, qv_des);

        nitem->setText(query.value(1).toString());

        ui->rmfList->addItem(nitem);
    }
}

RoomFeatures_Edit::~RoomFeatures_Edit()
{
    delete lastitem;
    delete ui;
}

void RoomFeatures_Edit::accept() {
    // checkInput();
}

void RoomFeatures_Edit::reject() {
    this->close();
}

/*
 * UserRole = ID
 * UserRole + 1 = description
 */

void RoomFeatures_Edit::displayItemInformation(QListWidgetItem* item) {
    // Check previous item
    if(lastitem == NULL) {
        lastitem = item;
        ui->featureNameEdit->setText(item->text());

        if(item->data(Qt::UserRole + 1).toString() == "") {
            ui->featureDeacriptionEdit->setPlaceholderText("No description found. Edit description in here");
        } else {
            ui->featureDeacriptionEdit->setText(item->data(Qt::UserRole + 1).toString());
        }
    } else {

    }

    QVariant data = item->data(Qt::UserRole);
    int idd = data.toInt();

    QVariant des = item->data(Qt::UserRole + 1);
    QString dstring = des.toString();

    qDebug() << "item id is " << idd << " and des is " << dstring;

}
