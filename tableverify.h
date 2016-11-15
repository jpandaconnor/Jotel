#ifndef TABLEVERIFY_H
#define TABLEVERIFY_H

#include <QWidget>

class TableVerify : public QWidget
{
    Q_OBJECT
public:
    explicit TableVerify(QWidget *parent = 0);
    void startChecking(QDialog* dialog);

signals:

public slots:

public:
     void checkTables();

private:
    void checkAdmin();
};

#endif // TABLEVERIFY_H
