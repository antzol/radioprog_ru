#include "customtablemodel.h"

#include <QtCore/QVector>
#include <QtCore/QTime>
#include <QtCore/QRect>
#include <QtCore/QRandomGenerator>
#include <QtGui/QColor>

#include <QDebug>

//---------------------------------------------------------------------------------------
CustomTableModel::CustomTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_columnCount = 2;
    headers << "ID" << "Some data";

    updateIdData(1, 1);
    updateIdData(2, 2);
//    updateIdData(3, 3);
    updateIdData(4, 4);
    updateIdData(5, 5);

    startTimer(1000);
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
            return ids.at(row);
        case ColumnSomeData:
            return someData.value(ids.at(row), 0);
        }
    }

    return QVariant();
}

//---------------------------------------------------------------------------------------
void CustomTableModel::updateIdData(int id, float bitrate)
{
    checkIdRow(id);
    someData[id] = bitrate;
    QModelIndex topLeft = createIndex(ids.indexOf(id),1);
    QModelIndex bottomRight = createIndex(ids.indexOf(id),1);
    emit dataChanged(topLeft, bottomRight, {Qt::DisplayRole});
}

//---------------------------------------------------------------------------------------
void CustomTableModel::checkIdRow(int id)
{
    if (!ids.contains(id))
    {
        beginInsertRows(QModelIndex(), ids.size(), ids.size());
        ids.append(id);
        someData[id] = 0;
        endInsertRows();
    }
}

//---------------------------------------------------------------------------------------
void CustomTableModel::deleteId(int id)
{
    int pos = ids.indexOf(id);
    if (pos != -1)
    {
        beginRemoveRows(QModelIndex(), pos, pos);
        ids.removeAt(pos);
        someData.remove(id);
        someData[id] = 0;
        endRemoveRows();
    }
}

//---------------------------------------------------------------------------------------
void CustomTableModel::timerEvent(QTimerEvent *ev)
{
    Q_UNUSED(ev)

    static int cnt = 0;

    switch (cnt)
    {
    case 3:
        updateIdData(3, 3);
        break;
    case 5:
        updateIdData(6, 6);
        break;
    case 7:
        deleteId(2);
        break;
    case 9:
        deleteId(5);
        break;
    }
    cnt++;
}

//---------------------------------------------------------------------------------------

