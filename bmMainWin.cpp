#include <QVBoxLayout>
#include "bmMainWin.h"

bmMainWin::bmMainWin(QWidget *parent)
    : QWidget(parent) {
    
    labelBmID = new QLabel(" 设备: ", this);
    labelBreathe = new QLabel(" 呼吸: ", this);
    labelHeartRate = new QLabel(" 心跳: ", this);

    auto *vbox = new QVBoxLayout();
    vbox->addWidget(labelBmID);
    vbox->addWidget(labelBreathe);
    vbox->addWidget(labelHeartRate);
    setLayout(vbox);
    
    //bmReader bm;

    //connect( &bm, &bmReader::serialPortErro, this, &bmMainWin::logErro );
    //connect( &bm, &bmReader::bmDataGot, this, &bmMainWin::logbmData );
    
    //bm.start();
}
void bmMainWin::logErro(const QString &s){
    labelBmID->setText(s);
    //QTextStream out(stdout);
    //out << QString(" 串口错误: %1").arg(s) << Qt::endl;
}
void bmMainWin::logbmData(const QString &bmID, const int Breathe, const int HeartRate){
    labelBmID->setText(QString(" 设备: %1").arg(bmID));
    labelBreathe->setText(QString(" 呼吸: %1").arg(Breathe));
    labelHeartRate->setText(QString(" 心跳: %1").arg(HeartRate));
    
    //QTextStream out(stdout);
    //out << QString(" 设备: %1").arg(bmID) << Qt::endl;
    //out << QString(" 呼吸: %1").arg(Breathe) << Qt::endl;
    //out << QString(" 心跳: %1").arg(HeartRate) << Qt::endl;
}
