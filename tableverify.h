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

private:
    void checkAdmin();
    void checkTables();
};

#endif // TABLEVERIFY_H
