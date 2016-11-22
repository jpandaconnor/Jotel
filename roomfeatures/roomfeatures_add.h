#ifndef ROOMFEATURES_ADD_H
#define ROOMFEATURES_ADD_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class RoomFeatures_Add;
}

class RoomFeatures_Add : public QDialog
{
    Q_OBJECT

public:
    explicit RoomFeatures_Add(QWidget *parent = 0);
    ~RoomFeatures_Add();

    void accept();
    void reject();

private:
    Ui::RoomFeatures_Add *ui;

    void checkInput();
};

#endif // ROOMFEATURES_ADD_H
