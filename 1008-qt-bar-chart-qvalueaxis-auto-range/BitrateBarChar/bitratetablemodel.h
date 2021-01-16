#ifndef BITRATETABLEMODEL_H
#define BITRATETABLEMODEL_H

#include <QAbstractTableModel>
#include <QMap>

class BitrateTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum {
        ColumnPid = 0,
        ColumnBitrate = 1
    };

    explicit BitrateTableModel(QObject *parent = 0);
    virtual ~BitrateTableModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

public slots:
    void updateEsBitrate(int pid, float bitrate);
    void checkPidRow(int pid);

protected:
    void timerEvent(QTimerEvent *ev);

private:
    void generateBitrateValues();

    QList<int> pids;
    QMap<int, double> bitrates;
    QStringList headers;
    int m_columnCount;

};

#endif // BITRATETABLEMODEL_H
