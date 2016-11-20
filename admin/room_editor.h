#ifndef ROOM_EDITOR_H
#define ROOM_EDITOR_H

#include <QDialog>

namespace Ui {
class Room_Editor;
}

class Room_Editor : public QDialog
{
    Q_OBJECT

public:
    explicit Room_Editor(QWidget *parent = 0);
    ~Room_Editor();
    
private slots:
    void on_addFloorButton_clicked();

    void on_deleteFloorButton_clicked();

    void on_addSectionButton_clicked();

    void on_deleteSectionButton_clicked();

    void on_roomList_doubleClicked(const QModelIndex &index);

    void on_roomList_clicked(const QModelIndex &index);

private:
    Ui::Room_Editor *ui;
};

#endif // ROOM_EDITOR_H
