#include <QVBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include "bmMainWin.h"

bmMainWin::bmMainWin(QWidget *parent)
    : QMainWindow(parent) {
    
    resize(500, 200);
    auto *quit = new QAction("退出", this);
    menuBar()->addMenu("人员管理");
    menuBar()->addMenu("设备管理");
    menuBar()->addMenu("系统管理");
    menuBar()->addMenu("查询统计");
    QMenu *exitMenu = menuBar()->addMenu("退出");
    exitMenu->addAction(quit);
    
    connect(quit, &QAction::triggered, this, &QMainWindow::close);
    
    labelBmID = new QLabel(" 设备: ", this);
    labelBreathe = new QLabel(" 呼吸: ", this);
    labelHeartRate = new QLabel(" 心跳: ", this);

    auto *vbox = new QVBoxLayout();
    vbox->addWidget(labelBmID);
    vbox->addWidget(labelBreathe);
    vbox->addWidget(labelHeartRate);
    vbox->addStretch(1);
    
    QWidget *mainWidget;
    mainWidget = new QWidget();
    mainWidget->setLayout(vbox);
    setCentralWidget(mainWidget);
}
void bmMainWin::logErro(const QString &s){
    statusBar()->showMessage(s);
}
void bmMainWin::logbmData(const QString &bmID, const int Breathe, const int HeartRate){
    labelBmID->setText(QString(" 设备: %1").arg(bmID));
    labelBreathe->setText(QString(" 呼吸: %1").arg(Breathe));
    labelHeartRate->setText(QString(" 心跳: %1").arg(HeartRate));
}

void bmMainWin::showEvent(QShowEvent *event){
    
    bm = new bmReader();

    connect( bm, &bmReader::serialPortErro, this, &bmMainWin::logErro );
    connect( bm, &bmReader::bmDataGot, this, &bmMainWin::logbmData );
    
    bm->start();
    QWidget::showEvent(event);
}

void bmMainWin::closeEvent(QCloseEvent *event){
    if (bm != 0 && bm->isRunning() ) {
        bm->requestInterruption();
        bm->wait();
    }
    QWidget::closeEvent(event);
}

