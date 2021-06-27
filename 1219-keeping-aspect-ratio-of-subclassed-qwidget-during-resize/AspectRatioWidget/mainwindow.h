#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCharts/QChart>
#include <QtCharts/QChartView>

QT_CHARTS_USE_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createSmithChart();
    QList<QPointF> createRCircle(double r);
    QList<QPointF> createXArc(double x);
    bool inRange(const QPointF &point);

    QChart *chart;
    QChartView *chartView;
};
#endif // MAINWINDOW_H
