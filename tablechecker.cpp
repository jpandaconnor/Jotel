#include "tablechecker.h"

TableChecker::TableChecker(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant TableChecker::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex TableChecker::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex TableChecker::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int TableChecker::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int TableChecker::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant TableChecker::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
