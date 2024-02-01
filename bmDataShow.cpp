
#include "bmDataShow.h"
#include "MonitorInfoPanel.h"
#include "EquMonitorObj.h"
#include "MonitorRoom.h"
#include "MonitorPerson.h"

bmDataShow::bmDataShow(QString bmID, QWidget *parent)
    : QWidget(parent) {
    this->bmID=bmID;
    seriesBreathe = new QLineSeries();
    seriesHeartRate = new QLineSeries();
    
    QToolBar *toolbar = new QToolBar(this);
    toolbar->setIconSize(QSize(16, 16));
    tagFullScreen = toolbar->addAction(QIcon(":/fullscreen.png"), "全屏");
    connect(tagFullScreen, &QAction::triggered, this, &bmDataShow::showFull);
    QAction *setMonitorobj = toolbar->addAction(QIcon(":/monitorobj.png"), "配置监测目标");
    connect(setMonitorobj, &QAction::triggered, this, &bmDataShow::setMonitorInfo);
    
    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(seriesBreathe);
    chart->addSeries(seriesHeartRate);
    
    axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("hh:mm:ss");
    axisX->setTitleText("时间");
    chart->addAxis(axisX, Qt::AlignBottom);
    seriesBreathe->attachAxis(axisX);
    seriesHeartRate->attachAxis(axisX);

    QDateTime tTime = QDateTime ::currentDateTime();
    axisX->setMin(tTime.addSecs(-120));
    axisX->setMax(tTime);
    
    axisY = new QValueAxis;
    axisY->setTickCount(12);
    axisY->setLabelFormat("%i");
    axisY->setTitleText("指标");
    chart->addAxis(axisY, Qt::AlignLeft);
    seriesBreathe->attachAxis(axisY);
    seriesHeartRate->attachAxis(axisY);
    axisY->setMin(0);
    axisY->setMax(120);
    
    // Customize chart title
    QFont font;
    font.setPixelSize(24);
    font.setBold(true);
    font.setWeight(QFont::Black);
    chart->setTitleFont(font);
    //chart->setTitleBrush(QBrush(Qt::red));
    chart->setTitle("体征实时数据");
    
    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setMargins(QMargins(0,0,0,0));
    chart->setBackgroundRoundness(0);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    
    
    auto *vbox = new QVBoxLayout();
    vbox->addWidget(toolbar,0); 
    
    QGroupBox *groupBox = new QGroupBox(QString(tr("设备：%1")).arg(bmID), this);
    groupBox->setAlignment(Qt::AlignHCenter);
    QVBoxLayout *groupvbox = new QVBoxLayout;     
    QFont bmDatafont;
    bmDatafont.setPixelSize(24);
    bmDatafont.setBold(true);
    bmDatafont.setWeight(QFont::Black);   
    BreatheLabel=new QLabel("呼吸：－－");
    BreatheLabel->setFont(bmDatafont);
    BreatheLabel->setStyleSheet("QLabel { color : red; }");
    HeartRateLabel=new QLabel("心跳：－－");
    HeartRateLabel->setFont(bmDatafont);
    HeartRateLabel->setStyleSheet("QLabel { color : red; }");
    groupvbox->addWidget(BreatheLabel);
    groupvbox->addWidget(HeartRateLabel);
    groupvbox->addStretch(1);
    groupBox->setLayout(groupvbox);
    vbox->addWidget(groupBox);
    
    MonitorObjGroupBox = new QGroupBox(QString(tr("监测目标")), this);
    MonitorObjGroupBox->setAlignment(Qt::AlignHCenter);
    groupvbox = new QVBoxLayout;  
    RoomLabel=new QLabel("房间：－－");
    PersonLabel=new QLabel("人员：－－");
    groupvbox->addWidget(RoomLabel);
    groupvbox->addWidget(PersonLabel);
    groupvbox->addStretch(1);
    MonitorObjGroupBox->setLayout(groupvbox);
    vbox->addWidget(MonitorObjGroupBox);
    
    vbox->addStretch(1);
    
    auto *hbox = new QHBoxLayout(this);
    hbox->addItem(vbox);
    hbox->addWidget(chartView, 1);
    
    showMonitorInfo();
}
void bmDataShow::addBmData(const int Breathe, const int HeartRate){
    
    if(Breathe>120 || Breathe<=0 || HeartRate>120 || HeartRate<=0){
    	return;
    }
    
    QDateTime tTime = QDateTime ::currentDateTime();
    
    if(seriesBreathe->count()>120){
    	seriesBreathe->remove(0);
    	seriesHeartRate->remove(0);
    }          

    axisX->setMin(tTime.addSecs(-120));
    axisX->setMax(tTime);
    
    seriesBreathe->append(tTime.toMSecsSinceEpoch(), Breathe);
    seriesHeartRate->append(tTime.toMSecsSinceEpoch(), HeartRate);
    
    HeartRateLabel->setText(QString("心跳: %1").arg(HeartRate));
    BreatheLabel->setText(QString("呼吸: %1").arg(Breathe));
    
    showMonitorInfo();
}
void bmDataShow::showFull(){
    isFull=(!isFull);
    emit askFullScreen(this, isFull);
    if(isFull){
        tagFullScreen->setIcon(QIcon(":/normalscreen.png")); 
	tagFullScreen->setText(QString("恢复"));	
    }
    else{
        tagFullScreen->setIcon(QIcon(":/fullscreen.png")); 
	tagFullScreen->setText(QString("全屏"));	
    }
}
void bmDataShow::setMonitorInfo(){
    MonitorInfoPanel *mip=new MonitorInfoPanel(bmID,this);    
    connect(mip, &MonitorInfoPanel::ok, this, &bmDataShow::showMonitorInfo);
    mip->show();
}
void bmDataShow::showMonitorInfo(){    
    //查询 监测对象配置表 若有记录，配置当前监测房间，人员
    equMonitorObj = EquMonitorObj::get()->selectByPk(bmID);
    if(equMonitorObj!=nullptr){
        monitorRoom = MonitorRoom::get()->selectByPk((*equMonitorObj)[EquMonitorObj::fRoomID]);
        if(monitorRoom!=nullptr){
            RoomLabel->setText(QString("房间: %1").arg((*monitorRoom)[MonitorRoom::fRoomCode]));
        }
        
        monitorPerson = MonitorPerson::get()->selectByPk((*equMonitorObj)[EquMonitorObj::fPersonID]);  
        if(monitorPerson!=nullptr){      
            PersonLabel->setText(QString("人员: %1").arg((*monitorPerson)[MonitorPerson::fPName]));
        }
    }
}


