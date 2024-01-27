#include <QVBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include "bmMainWin.h"
#include "EquManageWin.h"

bmMainWin::bmMainWin(QWidget *parent)
    : QMainWindow(parent) {
    setWindowIcon(QIcon(":/Main.png"));//只对windows有效，在linux下无效
    resize(800, 500);
    
    menuBar()->addMenu("人员管理");
    
    QMenu *exitMenu = menuBar()->addMenu("设备管理");
    auto *quit = new QAction(QIcon(":/House.png"),"设备管理", this);
    exitMenu->addAction(quit);
    connect(quit, &QAction::triggered, this, &bmMainWin::openEquManage);
    
    menuBar()->addMenu("系统管理");
    menuBar()->addMenu("查询统计");
    
    exitMenu = menuBar()->addMenu("退出");
    quit = new QAction(QIcon(":/Exit.png"),"退出", this);
    exitMenu->addAction(quit);
    connect(quit, &QAction::triggered, this, &QMainWindow::close);
    
    QToolBar *toolbar = addToolBar("main toolbar");
    startBm = toolbar->addAction(QIcon(":/Start.png"), "");

    connect(startBm, &QAction::triggered, this, &bmMainWin::changeStartStatus);
    

    mainWidget = new QWidget(this);
    
    vbox = new QVBoxLayout();
    mainWidget->setLayout(vbox);
    setCentralWidget(mainWidget);
}
void bmMainWin::logInfo(const QString &s){
    statusBar()->showMessage(s);
}
void bmMainWin::logbmData(const QString &bmID, const int Breathe, const int HeartRate){
    //此处加列表，以处理不同设备ID号？？
    if(bds == nullptr){
    	statusBar()->showMessage(QString("设备 %1 已连接").arg(bmID));
        bds=new bmDataShow(bmID, mainWidget);
        vbox->addWidget(bds,1);        
    }
    else{
    	statusBar()->showMessage(QString("已连接"));
    }
    
    bmStartStatus(started);

    bds->addBmData(Breathe, HeartRate);
}
void bmMainWin::bmStop(){
    	statusBar()->showMessage(QString("已断开"));
    bmStartStatus(stopped);
}

void bmMainWin::showEvent(QShowEvent *event){
        QWidget::showEvent(event);
}

void bmMainWin::closeEvent(QCloseEvent *event){
    if (bm != 0 && bm->isRunning() ) {
        bm->requestInterruption();
        bm->wait();
    }
    QWidget::closeEvent(event);
}

void bmMainWin::changeStartStatus(){
    startBmStatus targetStatus;
    if(m_startBmStatus==stopped){
    	targetStatus=loading_open;
    }
    else if(m_startBmStatus==started){
    	targetStatus=loading_close;
    }
    else if(m_startBmStatus==loading_open){
    	targetStatus=started;
    }
    else if(m_startBmStatus==loading_close){
    	targetStatus=stopped;
    }
    bmStartStatus(targetStatus);
}
void bmMainWin::bmStartStatus(startBmStatus targetStatus){
    if(targetStatus==stopped){
    	startBm->setIcon(QIcon(":/Start.png"));   		
	startBm->setEnabled(true);
	startBm->setToolTip(QString("开始"));
    }
    else if(targetStatus==started){    	
    	startBm->setIcon(QIcon(":/Stop.png"));   		
	startBm->setEnabled(true);
	startBm->setToolTip(QString("停止"));
    }
    else if(targetStatus==loading_open){
        //动画不成功
        //QMovie *loadMovie = new QMovie(this);
        //loadMovie->setFileName(":/Loading.gif");
    	//startBm->setIcon(loadMovie->currentPixmap());
    	//connect(loadMovie,SIGNAL(finished()),loadMovie,SLOT(start()));
        //loadMovie->start();
        
        startBm->setIcon(QIcon(":/Loading.png"));    		
	startBm->setEnabled(false);  
	startBm->setToolTip(QString("正在启动……"));
	
    	bm = new bmReader(this);
        connect( bm, &bmReader::serialPortErro, this, &bmMainWin::logInfo );
        connect( bm, &bmReader::bmDataGot, this, &bmMainWin::logbmData );   
        connect( bm, &bmReader::finished, this, &bmMainWin::bmStop );     
        bm->start();
    }
    else if(targetStatus==loading_close){
        if (bm != 0 && bm->isRunning() ) {
            bm->requestInterruption();
            bm->wait();            
        }
        
        startBm->setIcon(QIcon(":/Loading.png"));    		
	startBm->setEnabled(false);  
	startBm->setToolTip(QString("正在停止……"));
    }
    m_startBmStatus=targetStatus; 
}
void bmMainWin::openEquManage(){
    EquManageWin *emw=new EquManageWin(this);    
    emw->show();
}

