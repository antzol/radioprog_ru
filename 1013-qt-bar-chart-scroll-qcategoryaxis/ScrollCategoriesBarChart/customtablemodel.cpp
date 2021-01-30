#include "customtablemodel.h"

//---------------------------------------------------------------------------------------
CustomTableModel::CustomTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_columnCount = 2;
    headers << "ID" << "Some data";

    for(int i = 0; i <= 20; ++i)
        ids.append(i);
}

//---------------------------------------------------------------------------------------
CustomTableModel::~CustomTableModel()
{
}

//---------------------------------------------------------------------------------------
int CustomTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return ids.count();
}

//---------------------------------------------------------------------------------------
int CustomTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_columnCount;
}

//---------------------------------------------------------------------------------------
QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return headers.at(section);

    return QVariant();
}

//---------------------------------------------------------------------------------------
QVariant CustomTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    int row = index.row();
    int column = index.column();

    if (row >= rowCount() || column >= columnCount())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        switch (column)
        {
        case ColumnId:
        case ColumnSomeData:
            return ids.at(row);
        }
    }

    return QVariant();
}

//---------------------------------------------------------------------------------------


