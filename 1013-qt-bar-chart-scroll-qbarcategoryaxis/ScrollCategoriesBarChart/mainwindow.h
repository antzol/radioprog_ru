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
    const qreal BarSeriesHeight = 36;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void scrollCategoriesChart(int val);

protected:
    void showEvent(QShowEvent *ev);
    void resizeEvent(QResizeEvent *ev);

private:
    void updateChartCategories();

    Ui::MainWindow *ui;

    CustomTableModel *model;

    QVBarModelMapper *mapper;
    QChart *chart;
    QChartView *chartView;

    QScrollBar *categoriesScrollBar;
    int minCategoryNumber;
};
#endif // MAINWINDOW_H
