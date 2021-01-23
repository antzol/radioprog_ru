#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "customtablemodel.h"

#include <QtCharts>

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
    void processCategoryAdding(const QModelIndex &parentIndex, int first, int last);
    void processCategoryRemoving(const QModelIndex &parentIndex, int first, int last);

private:
    Ui::MainWindow *ui;

    CustomTableModel *model;

    QVBarModelMapper *mapper;
    QChart *chart;
    QChartView *chartView;
};
#endif // MAINWINDOW_H
