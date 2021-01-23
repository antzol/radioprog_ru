#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

//---------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new CustomTableModel(this);

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    chart = new QChart;

    QHorizontalBarSeries *series = new QHorizontalBarSeries;

    mapper = new QVBarModelMapper(this);
    mapper->setFirstBarSetColumn(CustomTableModel::ColumnSomeData);
    mapper->setLastBarSetColumn(CustomTableModel::ColumnSomeData);

    mapper->setSeries(series);
    mapper->setModel(model);

    chart->addSeries(series);

    int rowCount = model->rowCount();
    QStringList categories;
    for(int i = 0; i < rowCount; ++i)
    {
        QModelIndex idx = model->index(i, CustomTableModel::ColumnId);
        categories << model->data(idx).toString();
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
    axisX->setRange(0, 10);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(640, 480);

    ui->chartGroupBox->layout()->addWidget(chartView);

    connect(model, &CustomTableModel::rowsInserted,
            this, &MainWindow::processCategoryAdding);
    connect(model, &CustomTableModel::rowsAboutToBeRemoved,
            this, &MainWindow::processCategoryRemoving);

}

//---------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}

//---------------------------------------------------------------------------------------
void MainWindow::processCategoryAdding(const QModelIndex &parentIndex, int first, int last)
{
    Q_UNUSED(parentIndex)

    QList<QAbstractAxis *> vAxises = chart->axes(Qt::Vertical);
    if(vAxises.isEmpty())
        return;
    QBarCategoryAxis *axisY = qobject_cast<QBarCategoryAxis *>(vAxises.at(0));

    QModelIndex idx;
    for (int i = first; i <= last; ++i)
    {
        idx = model->index(i, CustomTableModel::ColumnId);
        QString category = model->data(idx).toString();
        axisY->insert(i, category);
    }
}

//---------------------------------------------------------------------------------------
void MainWindow::processCategoryRemoving(const QModelIndex &parentIndex, int first, int last)
{
    Q_UNUSED(parentIndex)

    QList<QAbstractAxis *> axises = chart->axes(Qt::Vertical);
    if(axises.isEmpty())
        return;
    QBarCategoryAxis *axisY = qobject_cast<QBarCategoryAxis *>(axises.at(0));

    for (int i = first; i <= last; ++i)
    {
        QModelIndex idx = model->index(i, CustomTableModel::ColumnId);
        QString category = model->data(idx).toString();
        axisY->remove(category);
    }
}

//---------------------------------------------------------------------------------------
