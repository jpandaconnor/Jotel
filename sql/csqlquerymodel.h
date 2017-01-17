#ifndef CSQLQUERYMODEL_H
#define CSQLQUERYMODEL_H

#include <QObject>
#include <QSqlQueryModel>
#include <QVariant>

class CSqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    CSqlQueryModel(QObject *parent = 0);

    QVariant data(const QModelIndex &item, int role) const Q_DECL_OVERRIDE;
};

#endif // CSQLQUERYMODEL_H
