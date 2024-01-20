
#include "bmDataShow.h"

bmDataShow::bmDataShow(QString bmID, QWidget *parent)
    : QWidget(parent) {
    this->bmID=bmID;
    seriesBreathe = new QLineSeries();
    seriesHeartRate = new QLineSeries();
    
    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(seriesBreathe);
    chart->addSeries(seriesHeartRate);
    
    axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("hh:mm:ss");
    axisX->setTitleText("时间");
    chart->addAxis(axisX, Qt::AlignBottom);
    seriesBreathe->attachAxis(axisX);
    seriesHeartRate->attachAxis(axisX);

    QDateTime tTime = QDateTime ::currentDateTime();
    axisX->setMin(tTime.addSecs(-120));
    axisX->setMax(tTime);
    
    axisY = new QValueAxis;
    axisY->setTickCount(12);
    axisY->setLabelFormat("%i");
    axisY->setTitleText("指标");
    chart->addAxis(axisY, Qt::AlignLeft);
    seriesBreathe->attachAxis(axisY);
    seriesHeartRate->attachAxis(axisY);
    axisY->setMin(0);
    axisY->setMax(120);
    
    // Customize chart title
    QFont font;
    font.setPixelSize(24);
    font.setBold(true);
    font.setWeight(QFont::Black);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::red));
    chart->setTitle("体征实时数据");
    
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
            
    auto *hbox = new QHBoxLayout(this);
    hbox->addWidget(chartView, 0);
}
void bmDataShow::addBmData(const int Breathe, const int HeartRate){
    
    if(Breathe>120 || Breathe<=0 || HeartRate>120 || HeartRate<=0){
    	return;
    }
    
    QDateTime tTime = QDateTime ::currentDateTime();
    
    if(seriesBreathe->count()>120){
    	seriesBreathe->remove(0);
    	seriesHeartRate->remove(0);
    }          

    axisX->setMin(tTime.addSecs(-120));
    axisX->setMax(tTime);
    
    seriesBreathe->append(tTime.toMSecsSinceEpoch(), Breathe);
    seriesHeartRate->append(tTime.toMSecsSinceEpoch(), HeartRate);
    
    chart->setTitle(QString("设备: %1  －  呼吸: %2  －  心跳: %3").arg(bmID).arg(Breathe).arg(HeartRate));
}
