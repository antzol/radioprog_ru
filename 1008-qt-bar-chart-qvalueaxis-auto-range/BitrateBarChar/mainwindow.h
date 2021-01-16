#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "bitratetablemodel.h"

#include <QtCharts>

#include <QSortFilterProxyModel>

QT_CHARTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void processBarSetValueChange(int index);
    void setAxisXMaxFromVal(double val, QValueAxis *axis);

private:
    Ui::MainWindow *ui;

    BitrateTableModel *model;

    QVBarModelMapper *mapper;
    QChart *chart;
    QChartView *chartView;
};
#endif // MAINWINDOW_H
