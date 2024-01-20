#pragma once
#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include "bmReader.h"
#include "bmDataShow.h"

class bmMainWin : public QMainWindow  {
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
public:
    bmMainWin(QWidget *parent = nullptr);

private:
    bmReader *bm;
    bmDataShow *bds;
    QVBoxLayout *vbox;
    QWidget *mainWidget;
public slots:
    void logErro(const QString &s);
    void logbmData(const QString &bmID, const int Breathe, const int HeartRate);
};
