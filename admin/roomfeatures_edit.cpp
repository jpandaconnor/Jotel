#include "roomfeatures_edit.h"
#include "ui_roomfeatures_edit.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QMessageBox>
#include <QListWidgetItem>

/*
 *
 * On close, check if anything needs savinga
 *
 */

QListWidgetItem* lastitem = NULL;

bool edited_name = false;
bool edited_des = false;

RoomFeatures_Edit::RoomFeatures_Edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoomFeatures_Edit)
{
    ui->setupUi(this);

    ui->deleteButton->setEnabled(false);
    ui->saveButton->setEnabled(false);
    ui->saveAllButton->setEnabled(false);

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    query.exec("SELECT * FROM jotel_features");

    while(query.next()) {
        QListWidgetItem* nitem = new QListWidgetItem;

        QVariant qv_id(query.value(0).toInt());

        QVariant qv_name(query.value(1).toString());
        QVariant qv_des(query.value(2).toString());

        QVariant qv_ename("0");
        QVariant qv_edess("0");

        nitem->setData(Qt::UserRole, qv_id);

        nitem->setData(Qt::UserRole + 1, qv_name);
        nitem->setData(Qt::UserRole + 2, qv_des);

        nitem->setData(Qt::UserRole + 3, qv_ename);
        nitem->setData(Qt::UserRole + 4, qv_edess);

        nitem->setText(query.value(1).toString());
        ui->rmfList->addItem(nitem);
    }

    if(ui->rmfList->count() == 0) {
        QMessageBox::warning(this, "No room features found", tr("No room features found. Press add to make a new feature"),
                             QMessageBox::Ok);
    }
}

RoomFeatures_Edit::~RoomFeatures_Edit()
{
    delete lastitem;
    delete ui;
}

void RoomFeatures_Edit::accept() {
}

void RoomFeatures_Edit::reject() {
    this->destroy();
}

void RoomFeatures_Edit::closeEvent(QCloseEvent* event) {
    bool nts = false;
    int listcount = ui->rmfList->count();

    for(int i = 0; i < listcount; i++) {
        if(ui->rmfList->item(i)->text().contains('*')) {
           nts = true;
        }
    }

    if(nts) {
        QMessageBox::StandardButton sts = QMessageBox::question(this, "Changes made",
                                                                "Do you want to exit without saving?",
                                                                QMessageBox::Yes | QMessageBox::No |
                                                                QMessageBox::Cancel);

        if(sts == QMessageBox::Yes) {
            // event->accept();
            this->destroy();
        } else {
            // event
        }
    }
}

/*
 * UserRole = ID
 * UserRole + 1 = ORIGINAL NAME
 * UserRole + 2 = DESCRIPTION
 *
 * UserRole + 3 = NAME THAT HAS BEEN EDITED
 * UserRole + 4 = DESCRIPTION THAT HAS BEEN EDITED
 */

void RoomFeatures_Edit::displayItemInformation(QListWidgetItem* item) {
        ui->saveButton->setEnabled(true);
        ui->saveAllButton->setEnabled(true);
        ui->deleteButton->setEnabled(true);

        if(lastitem == NULL) {
            lastitem = item;

            ui->featureNameEdit->setText(item->data(Qt::UserRole + 1).toString());

            if(item->data(Qt::UserRole + 2) == "0" || item->data(Qt::UserRole + 2) == "") {
                ui->featureDeacriptionEdit->clear();
                ui->featureDeacriptionEdit->setPlaceholderText("No description found. Edit feature description in here");
            } else {
                ui->featureDeacriptionEdit->setText(item->data(Qt::UserRole + 2).toString());
            }
        } else {
            if(item == lastitem) {
                return;
            }

            if(lastitem->data(Qt::UserRole + 3) != "0") {
                if(lastitem->data(Qt::UserRole + 3).toString() != ui->featureNameEdit->text()) {
                    QVariant qv_ename(ui->featureNameEdit->text());
                    lastitem->setData(Qt::UserRole + 3, qv_ename);
                }
            } else {
                if(lastitem->data(Qt::UserRole + 1).toString() != ui->featureNameEdit->text()) {
                    QVariant qv_ename(ui->featureNameEdit->text());
                    lastitem->setData(Qt::UserRole + 3, qv_ename);
                }
            }

            if(lastitem->data(Qt::UserRole + 4) != "0") {
                if(lastitem->data(Qt::UserRole + 4).toString() != ui->featureDeacriptionEdit->toPlainText()) {
                    QVariant qv_edes(ui->featureDeacriptionEdit->toPlainText());
                    lastitem->setData(Qt::UserRole + 4, qv_edes);
                }
            } else {
                if(lastitem->data(Qt::UserRole + 2).toString() != ui->featureDeacriptionEdit->toPlainText()) {
                    QVariant qv_edes(ui->featureDeacriptionEdit->toPlainText());
                    lastitem->setData(Qt::UserRole + 4, qv_edes);
                }
            }

            if(item->data(Qt::UserRole + 3) != "0") {
                ui->featureNameEdit->setText(item->data(Qt::UserRole + 3).toString());
            } else {
                ui->featureNameEdit->setText(item->data(Qt::UserRole + 1).toString());
            }

            if(item->data(Qt::UserRole + 4) != "0") {
                ui->featureDeacriptionEdit->setText(item->data(Qt::UserRole + 4).toString());
            } else {
                ui->featureDeacriptionEdit->setText(item->data(Qt::UserRole + 2).toString());
            }

            edited_name = false;
            edited_des = false;

            lastitem = item;
        }
}

void RoomFeatures_Edit::hasBeenEdited_Name(QString s) {
    if(ui->rmfList->currentItem()->data(Qt::UserRole + 1).toString() != ui->featureNameEdit->text()) {
        edited_name = true;
        if(!ui->rmfList->currentItem()->text().contains('*')) {
            ui->rmfList->currentItem()->setText(ui->rmfList->currentItem()->text() + " *");
        }
    } else {
        edited_name = false;

        if(ui->rmfList->currentItem()->text().contains('*')) {
            if(!edited_des && !edited_name) {
                ui->rmfList->currentItem()->setText(ui->rmfList->currentItem()->data(Qt::UserRole + 1).toString());
            }
        }
    }
}

void RoomFeatures_Edit::hasBeenEdited_Description() {
    if(ui->rmfList->currentItem()->data(Qt::UserRole + 2).toString() != ui->featureDeacriptionEdit->toPlainText()) {
        edited_des = true;
        if(!ui->rmfList->currentItem()->text().contains('*')) {
            ui->rmfList->currentItem()->setText(ui->rmfList->currentItem()->text() + " *");
        }
    } else {
        edited_des = false;

        if(ui->rmfList->currentItem()->text().contains('*')) {
            if(!edited_name && !edited_des) {
                ui->rmfList->currentItem()->setText(ui->rmfList->currentItem()->data(Qt::UserRole + 1).toString());
            }
        }
    }
}

void RoomFeatures_Edit::save() {
    if(!ui->rmfList->currentItem()->text().contains('*')) {
        QMessageBox::warning(this, "No changes found",
                             tr("Nothing has been edited for this feature"),
                             QMessageBox::Ok);
        return;
    }

    QSqlDatabase db = QSqlDatabase::database();

    QListWidgetItem* ci = ui->rmfList->currentItem();

    if(ci->data(Qt::UserRole + 1).toString() != ui->featureNameEdit->text()) {
        QVariant qv_name(ui->featureNameEdit->text());
        ci->setData(Qt::UserRole + 1, qv_name);
        ci->setText(ci->data(Qt::UserRole + 1).toString());

        QSqlQuery query(db);
        QString toexec(QString("UPDATE jotel_features SET name = '%1' WHERE id = '%2';").arg(
                           ui->featureNameEdit->text(), ci->data(Qt::UserRole).toString()));
        query.prepare(toexec);
        query.exec(toexec);
    }

    if(ci->data(Qt::UserRole + 2).toString() != ui->featureDeacriptionEdit->toPlainText()) {
        QVariant qv_des(ui->featureDeacriptionEdit->toPlainText());
        ci->setData(Qt::UserRole + 2, qv_des);

        if(ci->text().contains('*')) {
            ci->setText(ci->data(Qt::UserRole + 1).toString());
        }

        QSqlQuery query(db);
        QString toexec(QString("UPDATE jotel_features SET description = '%1' WHERE id = '%2';").arg(
                           ui->featureDeacriptionEdit->toPlainText(), ci->data(Qt::UserRole).toString()));
        query.prepare(toexec);
        query.exec(toexec);
    }

    QMessageBox::information(this, "Feature saved", "Feature has been saved", QMessageBox::Ok);
}

void RoomFeatures_Edit::save(QListWidgetItem *item) {
    QSqlDatabase db = QSqlDatabase::database();

    if(ui->rmfList->currentItem() == item) {
        if(item->data(Qt::UserRole + 1).toString() != ui->featureNameEdit->text()) {
            QVariant qv_name(ui->featureNameEdit->text());
            item->setData(Qt::UserRole + 1, qv_name);
            item->setText(item->data(Qt::UserRole + 1).toString());

            QSqlQuery query(db);
            QString toexec(QString("UPDATE jotel_features SET name = '%1' WHERE id = '%2';").arg(
                               ui->featureNameEdit->text(), item->data(Qt::UserRole).toString()));
            query.prepare(toexec);
            query.exec(toexec);
        }

        if(item->data(Qt::UserRole + 2).toString() != ui->featureDeacriptionEdit->toPlainText()) {
            QVariant qv_des(ui->featureDeacriptionEdit->toPlainText());
            item->setData(Qt::UserRole + 2, qv_des);

            if(item->text().contains('*')) {
                item->setText(item->data(Qt::UserRole + 1).toString());
            }

            QSqlQuery query(db);
            QString toexec(QString("UPDATE jotel_features SET description = '%1' WHERE id = '%2';").arg(
                               ui->featureDeacriptionEdit->toPlainText(), item->data(Qt::UserRole).toString()));
            query.prepare(toexec);
            query.exec(toexec);
        }
    } else {
        if(item->data(Qt::UserRole + 3) != "0") {
            QVariant qv_name(item->data(Qt::UserRole + 3).toString());
            QVariant qv_newname("0");

            item->setData(Qt::UserRole + 1, qv_name);
            item->setData(Qt::UserRole + 3, qv_newname);

            item->setText(item->data(Qt::UserRole + 1).toString());

            QSqlQuery query(db);
            QString toexec(QString("UPDATE jotel_features SET name = '%1' WHERE id = '%2';").arg(
                               item->text(), item->data(Qt::UserRole).toString()));
            query.prepare(toexec);
            query.exec(toexec);
        }

        if(item->data(Qt::UserRole + 4) != "0") {
            QVariant qv_des(item->data(Qt::UserRole + 4).toString());
            QVariant qv_newdes("0");

            item->setData(Qt::UserRole + 2, qv_des);
            item->setData(Qt::UserRole + 4, qv_newdes);

            if(item->text().contains('*')) {
                item->setText(item->data(Qt::UserRole + 1).toString());
            }

            QSqlQuery query(db);
            QString toexec(QString("UPDATE jotel_features SET description = '%1' WHERE id = '%2';").arg(
                               item->data(Qt::UserRole + 2).toString(), item->data(Qt::UserRole).toString()));
            query.prepare(toexec);
            query.exec(toexec);
        }
    }
}

void RoomFeatures_Edit::saveAll() {
    int listcount = ui->rmfList->count();

    if(listcount == 0) {
        QMessageBox::warning(this, "Nothing edited", "Cannot save all as no features have been edited", QMessageBox::Ok);
        return;
    }

    for(int i = 0; i < listcount; i++) {
        if(ui->rmfList->item(i)->text().contains('*')) {
           this->save(ui->rmfList->item(i));
        }
    }

    QMessageBox::information(this, "Saved", "All edited features have been saved", QMessageBox::Ok);
}

void RoomFeatures_Edit::addItem() {
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    int newid = ui->rmfList->count() + 1;

    QListWidgetItem* item = new QListWidgetItem;
    item->setText(QString("New feature %1").arg(newid));

    if(query.exec(QString("INSERT INTO jotel_features (name) VALUES ('%1');").arg(item->text()))) {
        QSqlQuery idquery(db);

        idquery.exec(QString("SELECT id FROM jotel_features WHERE name = '%1';").arg(item->text()));

        if(idquery.next()) {
            QVariant qv_id(idquery.value(0).toInt());
            QVariant qv_name(item->text());

            QVariant qv_ename("0");
            QVariant qv_edes("0");

            item->setData(Qt::UserRole, qv_id);
            item->setData(Qt::UserRole + 1, qv_name);

            item->setData(Qt::UserRole + 3, qv_ename);
            item->setData(Qt::UserRole + 4, qv_edes);

            ui->rmfList->addItem(item);
        }
    }
}

void RoomFeatures_Edit::deleteItem() {
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    QListWidgetItem* ci = ui->rmfList->currentItem();

    QMessageBox::StandardButton confirmation =
            QMessageBox::warning(this, "Delete feature", QString("Are you sure you want to delete feature '%1'?").arg(
                                                                        ci->text()), QMessageBox::Yes | QMessageBox::No);

    if(confirmation != QMessageBox::Yes) {
        return;
    }

    query.exec(QString("DELETE FROM jotel_features WHERE id = '%1'").arg(ci->data(Qt::UserRole).toInt()));
    ui->rmfList->takeItem(ui->rmfList->row(ci));

    QMessageBox::information(this, "Deleted", "Feature has been deleted", QMessageBox::Ok);
}
