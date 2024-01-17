#pragma once

#include <QWidget>
#include <QLabel>

class bmMainWin : public QWidget {

public:
    bmMainWin(QWidget *parent = nullptr);

private:
    QLabel *labelBreathe;
    QLabel *labelHeartRate;
    QLabel *labelBmID;
    
public slots:
    void logErro(const QString &s);
    void logbmData(const QString &bmID, const int Breathe, const int HeartRate);
};
