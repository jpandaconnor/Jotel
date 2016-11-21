#ifndef ROOMFEATURES_EDIT_H
#define ROOMFEATURES_EDIT_H

#include <QDialog>
#include <QListWidgetItem>
#include <QString>

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

private:
    Ui::RoomFeatures_Edit *ui;

    void checkInput();
};

#endif // ROOMFEATURES_EDIT_H
