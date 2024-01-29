#pragma once
#include <QWidget>
#include <QtCharts>

using namespace QtCharts;

class bmDataShow : public QWidget  {
    Q_OBJECT
    QLineSeries *seriesBreathe;
    QLineSeries *seriesHeartRate;
    QChart *chart;
    QDateTimeAxis *axisX;
    QValueAxis *axisY;
    QString bmID;
    QChartView qChartView;
    bool isFull=false;
    QAction *tagFullScreen;
public:
    bmDataShow(QString bmID, QWidget *parent = nullptr);
    void addBmData(const int Breathe, const int HeartRate);
public slots:
    void showFull();
signals:
    void askFullScreen(const bmDataShow* askBm,const bool isFull);
};
