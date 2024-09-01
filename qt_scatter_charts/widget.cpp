#include "widget.h"
#include <QtCharts/QtCharts>
QT_CHARTS_USE_NAMESPACE
#include "./ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
        ui->setupUi(this);
        this->setWindowTitle(QString("QtCharts Demo"));
        initChart();
}

void Widget::initChart()
{
        ui->chartView->setRenderHint(QPainter::Antialiasing);
        ui->chartView->chart()->setTitle("scatter graphic");
        ui->chartView->chart()->setDropShadowEnabled(false);
        ui->chartView->chart()->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
        ui->chartView->chart()->setTheme(QChart::ChartThemeBlueCerulean);
}

void Widget::on_pushButton_clicked()
{
	QScatterSeries* series = new QScatterSeries();
	series->setName("point style");
	series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
	series->setMarkerSize(10);

	for(int i = 0; i < 100; i++) {
		series->append(i, QRandomGenerator::global()->bounded(0, 100));
	}

	ui->chartView->chart()->addSeries(series);
	ui->chartView->chart()->createDefaultAxes();
}

Widget::~Widget()
{
    delete ui;
}

