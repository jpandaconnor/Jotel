#include "csqlquerymodel.h"

#include <QModelIndex>
#include <QVariant>

CSqlQueryModel::CSqlQueryModel(QObject *parent) : QSqlQueryModel(parent)
{

}

QVariant CSqlQueryModel::data(const QModelIndex &index, int role) const {
    QVariant value = QSqlQueryModel::data(index, role);
    if(value.isValid() && role == Qt::DisplayRole) {
        if(index.column() == 0) {
            return value.toString();
        } else if(index.column() == 1) {
            return value.toString();
        }
    }
}
