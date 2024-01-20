#pragma once
#include <QWidget>
#include <QtCharts>

using namespace QtCharts;

class bmDataShow : public QWidget  {
    QLineSeries *seriesBreathe;
    QLineSeries *seriesHeartRate;
    QChart *chart;
    QDateTimeAxis *axisX;
    QValueAxis *axisY;
    QString bmID;
public:
    bmDataShow(QString bmID, QWidget *parent = nullptr);
    void addBmData(const int Breathe, const int HeartRate);
private:
    QChartView qChartView;
public slots:

};
