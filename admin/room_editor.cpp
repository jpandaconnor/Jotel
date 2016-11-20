#include "room_editor.h"
#include "ui_room_editor.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QInputDialog>
#include <QTableWidgetItem>
#include <QDebug>
#include <QTreeWidgetItem>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QModelIndex>

Room_Editor::Room_Editor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Room_Editor)
{
    ui->setupUi(this);

    ui->addRoomButton->setEnabled(false);
    ui->editRoomButton->setEnabled(false);

    QSqlDatabase db = QSqlDatabase::database();

    ui->roomList->setSortingEnabled(true);

    QSqlQueryModel* modal = new QSqlQueryModel();
    QSqlQuery query(db);
    query.exec("SELECT id,name,description FROM jotel_rooms");
    modal->setQuery(query);
    modal->setHeaderData(0, Qt::Horizontal, tr("ID"));
    modal->setHeaderData(1, Qt::Horizontal, tr("Name"));
    modal->setHeaderData(2, Qt::Horizontal, tr("Description"));

    ui->roomList->setModel(modal);
    ui->roomList->setColumnHidden(0, true);

    /*
     *
     * Adding floor section
     *
     */
    QSqlQuery floor_query(db);

    floor_query.exec("SELECT * FROM jotel_floors");

    while(floor_query.next()) {
        QListWidgetItem* nitem = new QListWidgetItem;

        QVariant qv_id(floor_query.value(0).toInt());
        QVariant qv_no(floor_query.value(1).toInt());

        nitem->setData(Qt::UserRole, qv_id);
        nitem->setData(Qt::UserRole + 1, qv_no);

        nitem->setData(Qt::DisplayRole, floor_query.value(1).toInt());
        // nitem->setText(floor_query.value(1).toString());

        ui->floorList->addItem(nitem);
    }
    ui->floorList->setSortingEnabled(true);
    ui->floorList->sortItems(Qt::AscendingOrder);

    /*
     *
     * Adding sections section
     *
     */

    QSqlQuery section_query(db);
    section_query.exec("SELECT * FROM jotel_sections");

    while(section_query.next()) {
        QListWidgetItem* nitem = new QListWidgetItem;

        QVariant qv_id(section_query.value(0).toInt());
        QVariant qv_no(section_query.value(1).toInt());

        nitem->setData(Qt::UserRole, qv_id);
        nitem->setData(Qt::UserRole + 1, qv_no);

        nitem->setData(Qt::DisplayRole, section_query.value(1).toInt());
        // nitem->setText(section_query.value(1).toString());

        ui->sectionList->addItem(nitem);
    }
    ui->sectionList->setSortingEnabled(true);
    ui->sectionList->sortItems(Qt::AscendingOrder);
}

Room_Editor::~Room_Editor()
{
    delete ui;
}

void Room_Editor::on_addFloorButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    query.exec("SELECT * FROM jotel_rooms");

    int fornext = 0;

    if(query.next()) {
        fornext = query.size();
    }

    fornext++;
    bool ok;

    int floorno = QInputDialog::getInt(this, tr("New floor"), tr("Enter a new floor number"),
                                        fornext, 0, 999, 1, &ok);

    if(ok) {
        // if(floorno == 0) {
           // QMessageBox::critical(this, "Floor error", "You cannot have a floor numbered 0", QMessageBox::Ok);
           // return;
        // }

        QSqlQuery floorexists(db);
        floorexists.exec(QString("SELECT * FROM jotel_floors WHERE floor = %1").arg(floorno));

        if(!floorexists.next()) {
            QSqlQuery fta(db);
            fta.exec(QString("INSERT INTO jotel_floors (floor) VALUES (%1)").arg(floorno));
            QMessageBox::information(this, "New floor added", QString("A new floor with the number '%1' has been added").arg(floorno),
                                                                      QMessageBox::Ok);

            QListWidgetItem* item = new QListWidgetItem;

            QSqlQuery idgrab(db);
            idgrab.exec(QString("SELECT id FROM jotel_floors WHERE floor = '%1'").arg(floorno));

            if(idgrab.next()) {
                QVariant qv_id(idgrab.value(0).toInt());
                QVariant qv_floor(floorno);

                item->setData(Qt::UserRole, qv_id);
                item->setData(Qt::UserRole + 1, qv_floor);

                item->setData(Qt::DisplayRole, floorno);
                // item->setText(QString::number(floorno));

                ui->floorList->addItem(item);
                ui->floorList->sortItems(Qt::AscendingOrder);
            }
        } else {
            QMessageBox::critical(this, "Floor exists", QString("A floor with the number '%1' already exists").arg(floorno), QMessageBox::Ok);
        }
    }
}

void Room_Editor::on_deleteFloorButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();

    QListWidgetItem* ci = ui->floorList->currentItem();
    int id = ci->data(Qt::UserRole).toInt();

    QMessageBox::StandardButton confirmation =
            QMessageBox::warning(this, "Delete feature", QString("Are you sure you want to delete floor '%1'?").arg(
                                                                        QString::number(ci->data(Qt::UserRole + 1).toInt())), QMessageBox::Yes | QMessageBox::No);

    if(confirmation != QMessageBox::No) {
        QSqlQuery remove(db);
        remove.exec(QString("DELETE FROM jotel_floors WHERE id = %1").arg(id));

        ui->floorList->takeItem(ui->floorList->row(ci));

        QMessageBox::information(this, "Floor deleted", "Floor has been deleted", QMessageBox::Ok);
    }
}

void Room_Editor::on_addSectionButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    query.exec("SELECT * FROM jotel_sections");

    int fornext = 0;

    if(query.next()) {
        fornext = query.size();
    }

    fornext++;
    bool ok;

    int sectionno = QInputDialog::getInt(this, tr("New section"), tr("Enter a new section number"),
                                        fornext, 0, 999, 1, &ok);

    if(ok) {
        // if(floorno == 0) {
           // QMessageBox::critical(this, "Floor error", "You cannot have a floor numbered 0", QMessageBox::Ok);
           // return;
        // }

        QSqlQuery sectionexists(db);
        sectionexists.exec(QString("SELECT * FROM jotel_sections WHERE section = %1").arg(sectionno));

        if(!sectionexists.next()) {
            QSqlQuery fta(db);
            fta.exec(QString("INSERT INTO jotel_sections (section) VALUES (%1)").arg(sectionno));
            QMessageBox::information(this, "New section added", QString("A new section with the number '%1' has been added").arg(sectionno),
                                                                      QMessageBox::Ok);

            QListWidgetItem* item = new QListWidgetItem;

            QSqlQuery idgrab(db);
            idgrab.exec(QString("SELECT id FROM jotel_sections WHERE section = '%1'").arg(sectionno));

            if(idgrab.next()) {
                QVariant qv_id(idgrab.value(0).toInt());
                QVariant qv_section(sectionno);

                item->setData(Qt::UserRole, qv_id);
                item->setData(Qt::UserRole + 1, qv_section);

                // item->setText(QString::number(sectionno));
                item->setData(Qt::DisplayRole, sectionno);
                ui->sectionList->addItem(item);
                ui->sectionList->sortItems(Qt::AscendingOrder);
            }
        } else {
            QMessageBox::critical(this, "Section exists", QString("A section with the number '%1' already exists").arg(sectionno), QMessageBox::Ok);
        }
    }
}

void Room_Editor::on_deleteSectionButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();

    QListWidgetItem* ci = ui->sectionList->currentItem();
    int id = ci->data(Qt::UserRole).toInt();

    QMessageBox::StandardButton confirmation =
            QMessageBox::warning(this, "Delete section", QString("Are you sure you want to delete section '%1'?").arg(
                                                                        QString::number(ci->data(Qt::UserRole + 1).toInt())), QMessageBox::Yes | QMessageBox::No);

    if(confirmation != QMessageBox::No) {
        QSqlQuery remove(db);
        remove.exec(QString("DELETE FROM jotel_sections WHERE id = %1").arg(id));

        ui->sectionList->takeItem(ui->sectionList->row(ci));

        QMessageBox::information(this, "Section deleted", "Section has been deleted", QMessageBox::Ok);
    }
}

void Room_Editor::on_roomList_doubleClicked(const QModelIndex &index)
{
    // QModelIndex new_idx = index1.model()->index(index1.row(), 0);
    QModelIndex inx = index.model()->index(index.row(), 0);

}

void Room_Editor::on_roomList_clicked(const QModelIndex &index)
{
    ui->addRoomButton->setEnabled(true);
    ui->editRoomButton->setEnabled(true);
}
