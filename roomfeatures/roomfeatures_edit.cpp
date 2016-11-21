#include "roomfeatures_edit.h"
#include "ui_roomfeatures_edit.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include <QVariant>
#include <QMessageBox>
#include <QListWidgetItem>

// const QListWidgetItem* lastitem;

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
        QVariant qv_name(query.value(1).toString());

        nitem->setData(Qt::UserRole, qv_id);
        nitem->setData(Qt::UserRole + 1, qv_name);
        nitem->setData(Qt::UserRole + 2, qv_des);

        nitem->setText(query.value(1).toString());

        ui->rmfList->addItem(nitem);
    }
}

RoomFeatures_Edit::~RoomFeatures_Edit()
{
    // delete lastitem;
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
 * UserRole + 1 = name
 * UserRole + 2 = des
 *
 *
 *
 */

/*
void RoomFeatures_Edit::displayItemInformation(QListWidgetItem* item) {
    // Check previous item

    qDebug() << "Text is: " << item->text();
    if(lastitem == NULL) {
        qDebug() << "NULL as fuck";
        lastitem = item;
        // ui->featureNameEdit->setText(item->data(Qt::UserRole + 1));

        if(item->data(Qt::UserRole + 2).toString() == "") {
            ui->featureDeacriptionEdit->setPlaceholderText("No description found. Edit description in here");
        } else {
            ui->featureDeacriptionEdit->setText(item->data(Qt::UserRole + 2).toString());
        }
    } else {
          // ui->featureNameEdit->setText(item->data(Qt::UserRole + 1));
          qDebug() << "Now not null";
        // In the to-be last item at the moment

        // Here, checking if assigned name is not same as name in box
        qDebug() << "THING: " << lastitem->data(Qt::UserRole + 1).toString();
        if(lastitem->data(Qt::UserRole + 1).toString() != ui->featureNameEdit->text()) {
            // lastitem->setText(lastitem->text() + " (Edited)");
            qDebug() << "What it should be " << lastitem->text() << " (Edited)";
            // Add as a new QVariant
        }

        // Yucky comparison of description here
        if(lastitem->data(Qt::UserRole + 1).toString() != ui->featureDeacriptionEdit->toPlainText()) {
            // Add as a new QVariant
        }



        lastitem = item;
    }

    QVariant data = item->data(Qt::UserRole);
    int idd = data.toInt();

    QVariant des = item->data(Qt::UserRole + 1);
    QString dstring = des.toString();

    qDebug() << "item id is " << idd << " and des is " << dstring;

}

*/
