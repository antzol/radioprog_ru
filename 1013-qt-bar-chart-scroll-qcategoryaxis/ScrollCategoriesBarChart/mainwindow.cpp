#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

//---------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , minCategoryNumber(0)
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
    axisX->setRange(0, 20);
    axisX->setTickCount(11);

    chart->setContentsMargins(-10, -10, -10, -10);
    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->legend()->hide();

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(5*BarSeriesHeight);

    categoriesScrollBar = new QScrollBar(Qt::Vertical);
    categoriesScrollBar->setValue(0);
    categoriesScrollBar->setInvertedAppearance(true);
    connect(categoriesScrollBar, &QScrollBar::valueChanged,
            this, &MainWindow::scrollCategoriesChart);

    ui->chartGroupBox->layout()->addWidget(chartView);
    ui->chartGroupBox->layout()->addWidget(categoriesScrollBar);
}

//---------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}

//---------------------------------------------------------------------------------------
void MainWindow::scrollCategoriesChart(int val)
{
    minCategoryNumber = val;
    updateChartCategories();
}

//---------------------------------------------------------------------------------------
void MainWindow::showEvent(QShowEvent *ev)
{
    QMainWindow::showEvent(ev);
    updateChartCategories();
}

//---------------------------------------------------------------------------------------
void MainWindow::resizeEvent(QResizeEvent *ev)
{
    QMainWindow::resizeEvent(ev);
    updateChartCategories();
}

//---------------------------------------------------------------------------------------
void MainWindow::updateChartCategories()
{
    QList<QAbstractAxis *> axises = chart->axes(Qt::Vertical);
    if (axises.isEmpty())
        return;

    QBarCategoryAxis *axisY = qobject_cast<QBarCategoryAxis *>(axises.at(0));

    auto categories = axisY->categories();
    if (categories.isEmpty())
        return;

    int catCount = categories.size();
    int catRange = chartView->height() / BarSeriesHeight;
    if (catCount < catRange)
        catRange = catCount;

    int maxCategoryNumber = minCategoryNumber + catRange - 1;
    if(maxCategoryNumber >= catCount)
        maxCategoryNumber = catCount - 1;

    QString minCategoryName = categories.at(minCategoryNumber);
    QString maxCategoryName = categories.at(maxCategoryNumber);
    axisY->setMin(minCategoryName);
    axisY->setMax(maxCategoryName);

    categoriesScrollBar->setRange(0, catCount - catRange);
}

//---------------------------------------------------------------------------------------
