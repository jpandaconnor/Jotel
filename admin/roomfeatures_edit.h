#ifndef ROOMFEATURES_EDIT_H
#define ROOMFEATURES_EDIT_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class RoomFeatures_Edit;
}

class RoomFeatures_Edit : public QDialog
{
    Q_OBJECT

public:
    explicit RoomFeatures_Edit(QWidget *parent = 0);
    ~RoomFeatures_Edit();

    void accept();
    void reject();

public slots:
    void displayItemInformation(QListWidgetItem* item);

    void hasBeenEdited_Name(QString s);
    void hasBeenEdited_Description();

    void save();
    void saveAll();

    void addItem();
    void deleteItem();

private:
    Ui::RoomFeatures_Edit *ui;

    void closeEvent(QCloseEvent* event);
    void save(QListWidgetItem* item);
};

#endif // ROOMFEATURES_EDIT_H
