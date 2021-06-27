#include "mainwindow.h"

#include "aspectratiowidget.h"

#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>

#include <cmath>
#include <array>

static constexpr double PI = 3.14159265;

static constexpr std::array circlesValues{0.0, 0.1, 0.2, 0.4, 0.6, 0.8, 1.0, 1.4,
                                          2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};

static constexpr std::array arcsValues{0.1, 0.2, 0.3, 0.4, 0.6, 0.8, 1.0,
                                       1.2, 1.4, 1.6, 1.8,
                                       2.0, 3.0, 4.0, 5.0 };

//---------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createSmithChart();

    //setCentralWidget(chartView);

    AspectRatioWidget *wgt = new AspectRatioWidget(chartView, 400, 400);
    setCentralWidget(wgt);

    setWindowTitle("Aspect Ratio");
    resize(400, 400);
}

//---------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
}

//---------------------------------------------------------------------------------------
void MainWindow::createSmithChart()
{
    chart = new QChart();

    for (auto r : circlesValues)
    {
        QSplineSeries *series = new QSplineSeries();
        series->append(createRCircle(r));
        chart->addSeries(series);
    }

    for (auto x : arcsValues)
    {
        if (!x)
            continue;

        QSplineSeries *series = new QSplineSeries();
        series->append(createXArc(x));
        chart->addSeries(series);

        QSplineSeries *nseries = new QSplineSeries();
        nseries->append(createXArc(-x));
        chart->addSeries(nseries);
    }

    chart->createDefaultAxes();
    chart->legend()->hide();

    QList<QAbstractAxis*> hAxes = chart->axes(Qt::Horizontal);
    if(!hAxes.isEmpty())
        hAxes.first()->setRange(-1, 1);

    chartView = new QChartView();
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

//---------------------------------------------------------------------------------------
QList<QPointF> MainWindow::createRCircle(double r)
{
    QList<QPointF> points;

    for (int degree = 0; degree <= 360; ++degree)
    {
        double radius = 1.0 / (r + 1);
        double xCenter = r / (r + 1);
        double x = radius * cos(degree * PI / 180) + xCenter;
        double y = radius * sin(degree * PI / 180);
        points.append(QPointF(x, y));
    }

    return points;
}

//---------------------------------------------------------------------------------------
QList<QPointF> MainWindow::createXArc(double x)
{
    QList<QPointF> points;

    if (!x)
        return points;

    double radius = 1.0 / x;
    double xCenter = 1.0;
    double yCenter = 1.0 / x;
    double degree = 90;
    while(1)
    {
        double x = radius * cos(degree * PI / 180) + xCenter;
        double y = radius * sin(degree * PI / 180) + yCenter;
        QPointF p = QPointF(x, y);
        if (inRange(p))
            points.append(p);

        degree += 0.1;
        if(degree > 450)
            break;
    }

    return points;
}

//---------------------------------------------------------------------------------------
bool MainWindow::inRange(const QPointF &point)
{
    double radius = 1.0 ;
    double centerX = 0.0;
    double centerY = 0.0;

    return (pow(point.x() - centerX, 2) + pow(point.y() - centerY, 2)) <= pow(radius, 2);
}

//---------------------------------------------------------------------------------------
