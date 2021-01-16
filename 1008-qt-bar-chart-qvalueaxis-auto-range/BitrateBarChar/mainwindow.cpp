#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

//---------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new BitrateTableModel;

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    model->setParent(ui->tableView);

    chart = new QChart;

    QHorizontalBarSeries *series = new QHorizontalBarSeries;

    mapper = new QVBarModelMapper(this);
    mapper->setFirstBarSetColumn(BitrateTableModel::ColumnBitrate);
    mapper->setLastBarSetColumn(BitrateTableModel::ColumnBitrate);

    mapper->setSeries(series);
    mapper->setModel(model);

    chart->addSeries(series);

    int rowCount = model->rowCount();
    QStringList categories;
    qreal maxValue = 0;
    for(int i = 0; i < rowCount; ++i)
    {
        QModelIndex idx = model->index(i, BitrateTableModel::ColumnPid);
        categories << model->data(idx).toString();

        idx = model->index(i, BitrateTableModel::ColumnBitrate);
        qreal curValue = model->data(idx).toDouble();
        if (curValue > maxValue)
            maxValue = curValue;
    }

    QBarCategoryAxis *axisY = new QBarCategoryAxis();
    axisY->setGridLineVisible(false);
    axisY->setLineVisible(false);
    axisY->append(categories);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QValueAxis *axisX = new QValueAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    setAxisXMaxFromVal(maxValue, axisX);

    QList<QBarSet*> barsets = series->barSets();
    for(int i = 0; i < barsets.size(); ++i)
    {
        connect(barsets.at(i), &QBarSet::valueChanged,
                this, &MainWindow::processBarSetValueChange);
    }

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(640, 480);

    ui->chartGroupBox->layout()->addWidget(chartView);
}

//---------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}

//---------------------------------------------------------------------------------------
void MainWindow::processBarSetValueChange(int index)
{
    QList<QAbstractAxis *> hAxises = chart->axes(Qt::Horizontal);
    if(hAxises.isEmpty())
        return;
    QValueAxis *axisX = qobject_cast<QValueAxis *>(hAxises.at(0));

    QBarSet *barset = qobject_cast<QBarSet*>(sender());
    qreal value = barset->at(index);

    if (value > axisX->max())
        setAxisXMaxFromVal(value, axisX);
}

//---------------------------------------------------------------------------------------
void MainWindow::setAxisXMaxFromVal(double val, QValueAxis *axis)
{
    int degree = (int)floor(log10(abs(val)));
    int scaled = val * pow(10, -degree);
    int step2 = ((scaled +4)/5)*5;
    int maxValue = step2 * pow(10, degree);

    axis->setMax(maxValue);
}

//---------------------------------------------------------------------------------------
