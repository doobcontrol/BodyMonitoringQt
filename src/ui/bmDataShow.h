#pragma once
#include <QWidget>
#include <QChart>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QChartView>
#include <QLabel>
#include <QGroupBox>
#include <QMediaPlayer>
#include <QMovie>

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
    bool inRecord=false;
    QAction *tagFullScreen;
    QAction *record;
    QAction *setMonitorobj;
    QLabel* BreatheLabel;
    QLabel* HeartRateLabel;
    QGroupBox *MonitorObjGroupBox;
    QLabel* RoomLabel;
    QLabel* PersonLabel;
    QLabel* PhotoLabel;
    QLabel* alertLabel;
    QMap<QString, QString>* equMonitorObj=nullptr;
    QMap<QString, QString>* monitorRoom=nullptr;
    QMap<QString, QString>* monitorPerson=nullptr;
    QMovie *movie=nullptr;
    QMediaPlayer *sound=nullptr;
    QString recordID;
public:
    bmDataShow(QString bmID, QWidget *parent = nullptr);
    void addBmData(const int Breathe, const int HeartRate);
    bool eventFilter(QObject *watched, QEvent *event);
public slots:
    void showFull();
    void recordData();
    void setMonitorInfo();
    void showMonitorInfo();
    void checkAlert(const int Breathe, const int HeartRate);
    void startAlert();
    void stopAlert();
signals:
    void askFullScreen(const bmDataShow* askBm,const bool isFull);
};
