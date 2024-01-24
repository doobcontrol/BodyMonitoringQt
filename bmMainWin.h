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
    enum BmStatusType {
        started = 0,
        loading_open,
        loading_close,
        stopped
    };  Q_DECLARE_FLAGS(startBmStatus, BmStatusType)
private:
    bmReader *bm = nullptr; //指针不赋此初值导致 bm != 0 总是为true
    bmDataShow *bds = nullptr;
    QVBoxLayout *vbox;
    QWidget *mainWidget;
    startBmStatus m_startBmStatus=stopped;
    QAction *startBm;
    void bmStartStatus(startBmStatus targetStatus);
public slots:
    void logInfo(const QString &s);
    void logbmData(const QString &bmID, const int Breathe, const int HeartRate);
    void changeStartStatus();
    void loadMovieFrameChanged_Handler(int frameNumber);
    void bmStop();
};
Q_DECLARE_OPERATORS_FOR_FLAGS(bmMainWin::startBmStatus)
