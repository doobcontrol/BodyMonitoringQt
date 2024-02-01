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
    QLabel* BreatheLabel;
    QLabel* HeartRateLabel;
    QGroupBox *MonitorObjGroupBox;
    QLabel* RoomLabel;
    QLabel* PersonLabel;
    QMap<QString, QString>* equMonitorObj=nullptr;
    QMap<QString, QString>* monitorRoom=nullptr;
    QMap<QString, QString>* monitorPerson=nullptr;
public:
    bmDataShow(QString bmID, QWidget *parent = nullptr);
    void addBmData(const int Breathe, const int HeartRate);
public slots:
    void showFull();
    void setMonitorInfo();
    void showMonitorInfo();
signals:
    void askFullScreen(const bmDataShow* askBm,const bool isFull);
};
