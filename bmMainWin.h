#pragma once
#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include "bmReader.h"

class bmMainWin : public QMainWindow  {
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
public:
    bmMainWin(QWidget *parent = nullptr);

private:
    QLabel *labelBreathe;
    QLabel *labelHeartRate;
    QLabel *labelBmID;
    bmReader *bm;
    
public slots:
    void logErro(const QString &s);
    void logbmData(const QString &bmID, const int Breathe, const int HeartRate);
};
