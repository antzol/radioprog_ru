#ifndef CUSTOMTABLEMODEL_H
#define CUSTOMTABLEMODEL_H

#include <QAbstractTableModel>
#include <QMap>

class CustomTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum {
        ColumnId = 0,
        ColumnSomeData = 1
    };

    explicit CustomTableModel(QObject *parent = 0);
    virtual ~CustomTableModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

public slots:
    void updateIdData(int id, float bitrate);
    void checkIdRow(int id);
    void deleteId(int id);
//    void timerHint();


protected:
    void timerEvent(QTimerEvent *ev);

private:

    QList<int> ids;
    QMap<int, double> someData;
    QStringList headers;
    int m_columnCount;

};

#endif // CUSTOMTABLEMODEL_H
