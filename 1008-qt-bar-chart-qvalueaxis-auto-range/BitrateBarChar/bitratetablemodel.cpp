#include "bitratetablemodel.h"

#include <QtCore/QVector>
#include <QtCore/QTime>
#include <QtCore/QRect>
#include <QtCore/QRandomGenerator>
#include <QtGui/QColor>

#include <QDebug>

//---------------------------------------------------------------------------------------
BitrateTableModel::BitrateTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_columnCount = 2;
    headers << "PID" << "Bitrate, kbit/s";

    updateEsBitrate(0, 0);
    updateEsBitrate(1020, 0);
    updateEsBitrate(1021, 0);
    updateEsBitrate(1022, 0);
    updateEsBitrate(1024, 0);
    updateEsBitrate(1070, 0);
    updateEsBitrate(1071, 0);
    updateEsBitrate(1072, 0);
    updateEsBitrate(1074, 0);
    updateEsBitrate(1090, 0);
    updateEsBitrate(1091, 0);
    updateEsBitrate(1092, 0);
    updateEsBitrate(1094, 0);

    startTimer(500);
}

//---------------------------------------------------------------------------------------
BitrateTableModel::~BitrateTableModel()
{
}

//---------------------------------------------------------------------------------------
int BitrateTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return pids.count();
}

//---------------------------------------------------------------------------------------
int BitrateTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_columnCount;
}

//---------------------------------------------------------------------------------------
QVariant BitrateTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return headers.at(section);

    return QVariant();
}

//---------------------------------------------------------------------------------------
QVariant BitrateTableModel::data(const QModelIndex &index, int role) const
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
        case ColumnPid:
            return pids.at(row);
        case ColumnBitrate:
            return bitrates.value(pids.at(row), 0);
        }
    }

    return QVariant();
}

//---------------------------------------------------------------------------------------
void BitrateTableModel::updateEsBitrate(int pid, float bitrate)
{
    checkPidRow(pid);
    bitrates[pid] = bitrate;
    QModelIndex topLeft = createIndex(pids.indexOf(pid), ColumnBitrate);
    QModelIndex bottomRight = createIndex(pids.indexOf(pid), ColumnBitrate);
    emit dataChanged(topLeft, bottomRight, {Qt::DisplayRole});
}

//---------------------------------------------------------------------------------------
void BitrateTableModel::checkPidRow(int pid)
{
    if (!pids.contains(pid))
    {
        beginInsertRows(QModelIndex(), pids.size(), pids.size());
        pids.append(pid);
        bitrates[pid] = 0;
        endInsertRows();
    }
}

//---------------------------------------------------------------------------------------
void BitrateTableModel::timerEvent(QTimerEvent *ev)
{
    Q_UNUSED(ev)
    generateBitrateValues();
}

//---------------------------------------------------------------------------------------
void BitrateTableModel::generateBitrateValues()
{
    static int t = 0;
    int minVideoBitrate = (t++ > 10) ? 7600 : 2650;


    for(int i = 0; i < pids.size(); ++i)
    {
        int pid = pids.at(i);

		switch (pid % 10)
		{
		case 0:
			updateEsBitrate(pid, rand() % 10 + 15);
			break;
		case 1:
            updateEsBitrate(pid, rand() % 100 + minVideoBitrate);
			break;
		case 2:
			updateEsBitrate(pid, rand() % 20 + 180);
			break;
		case 4:
			updateEsBitrate(pid, rand() % 10 + 35);
			break;
		default:
            updateEsBitrate(pid, 0);
		}
    }
}

//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
