#include <QVBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include "bmMainWin.h"

bmMainWin::bmMainWin(QWidget *parent)
    : QMainWindow(parent) {
    
    resize(800, 500);
    auto *quit = new QAction("退出", this);
    menuBar()->addMenu("人员管理");
    menuBar()->addMenu("设备管理");
    menuBar()->addMenu("系统管理");
    menuBar()->addMenu("查询统计");
    QMenu *exitMenu = menuBar()->addMenu("退出");
    exitMenu->addAction(quit);
    
    connect(quit, &QAction::triggered, this, &QMainWindow::close);

    mainWidget = new QWidget(this);
    
    vbox = new QVBoxLayout();
        bds=new bmDataShow(mainWidget);
        //bds->bmID=bmID;
        vbox->addWidget(bds,1);
    
    mainWidget->setLayout(vbox);
    setCentralWidget(mainWidget);
}
void bmMainWin::logErro(const QString &s){
    statusBar()->showMessage(s);
}
void bmMainWin::logbmData(const QString &bmID, const int Breathe, const int HeartRate){
    //此处加列表，以处理不同设备ID号？？
    if(bds==0){
        bds=new bmDataShow(mainWidget);
        bds->bmID=bmID;
        vbox->addWidget(bds,1);
    }
    bds->bmID=bmID;

    bds->addBmData(Breathe, HeartRate);
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

