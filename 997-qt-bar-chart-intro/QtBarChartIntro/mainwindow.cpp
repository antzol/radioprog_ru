#include "mainwindow.h"

#include <cmath>

#include <QtCharts>

using namespace QtCharts;

//---------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QBarSet *centralFedDistr = new QBarSet("Центральный");
    QBarSet *northwesternDistr = new QBarSet("Северо-Западный");
    QBarSet *southerhFedDistr = new QBarSet("Южный");
    QBarSet *northCaucasianFedDistr = new QBarSet("Северо-Кавказский");
    QBarSet *volgaFedDistr = new QBarSet("Приволжский");
    QBarSet *uralFedDistr = new QBarSet("Уральский");
    QBarSet *siberianFedDistr = new QBarSet("Сибирский");
    QBarSet *farEasternFedDistr = new QBarSet("Дальневосточный");

    *centralFedDistr        << 3378.83 << 3304.0 << 3261.0 << 2927.4;
    *northwesternDistr      << 1261.83 << 1268.6 << 1253.4 << 1096.3;
    *southerhFedDistr       << 823.45  << 821.8  << 781.5  << 821.6;
    *northCaucasianFedDistr << 295.39  << 313.7  << 312.8  << 197.1;
    *volgaFedDistr          << 2291.97 << 2312.6 << 2222.4 << 1992.1;
    *uralFedDistr           << 921.92  << 891.5  << 862.1  << 834.8;
    *siberianFedDistr       << 1349.41 << 1362.9 << 1313.8 << 1139.8;
    *farEasternFedDistr     << 455.14  << 469.7  << 458.0  << 382.7;


    QBarSeries *series = new QBarSeries();
    series->append(centralFedDistr);
    series->append(northwesternDistr);
    series->append(southerhFedDistr);
    series->append(northCaucasianFedDistr);
    series->append(volgaFedDistr);
    series->append(uralFedDistr);
    series->append(siberianFedDistr);
    series->append(farEasternFedDistr);

    QList<QBarSet *> sets = series->barSets();
    float currentHue = 0.0;
    for(int i = 0; i < sets.size(); ++i)
    {
        QColor col = QColor::fromHslF(currentHue, 0.7, 0.5);
        currentHue += 0.618033988749895f;
        currentHue = std::fmod(currentHue, 1.0f);
        sets[i]->setColor(col);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Среднесписочная численность работников предприятий малого и среднего бизнеса по федеральным округам");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "01.01.2014" << "01.01.2015" << "01.01.2016" << "01.01.2017";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,4000);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    setCentralWidget(chartView);
    resize(800, 400);
}

//---------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
}

//---------------------------------------------------------------------------------------
