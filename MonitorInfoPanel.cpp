#include "MonitorInfoPanel.h"
#include "EquMonitorObj.h"
#include "MonitorRoom.h"
#include "MonitorPerson.h"
#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

MonitorInfoPanel::MonitorInfoPanel(QString bmID, QWidget *parent)
    : QMainWindow(parent) {   
    this->bmID=bmID;
    getMonitorInfo();
    setWindowTitle("配置监测目标"); 
    setWindowIcon(QIcon(":/monitorobj.png"));//只对windows有效，在linux下无效
    resize(400, 300);
    setWindowModality(Qt::ApplicationModal);  
    
    int rowCount=0;
    
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->addWidget(new QLabel("监测设备："),rowCount,0,1,1);
    gridLayout->addWidget(new QLabel(bmID),rowCount,1,1,1);
    
    rowCount++;
    gridLayout->addWidget(new QLabel("房间："),rowCount,0,1,1);
    gridLayout->addWidget(&roomIDEdit,rowCount,1,1,1);
    
    rowCount++;
    QListWidget *roomlistWidget = new QListWidget(this);
    gridLayout->addWidget(roomlistWidget,rowCount,1,1,1);
    QList<QMap<QString, QString>>* roomRowList = MonitorRoom::get()->selectAll();
    for(QMap<QString, QString> roomRow:(*roomRowList)){
        new QListWidgetItem(roomRow[MonitorRoom::fRoomCode], roomlistWidget);
    }
    
    rowCount++;
    gridLayout->addWidget(new QLabel("姓名："),rowCount,0,1,1);
    gridLayout->addWidget(&personNameEdit,rowCount,1,1,1);    
    
    rowCount++;
    QListWidget *namelistWidget = new QListWidget(this);
    gridLayout->addWidget(namelistWidget,rowCount,1,1,1);
    
    auto *vbox = new QVBoxLayout();
    vbox->addItem(gridLayout);
    vbox->addStretch(1);
    
    QPushButton* tQpb;
    auto *hbox = new QHBoxLayout();
    hbox->addStretch(1);
    tQpb=new QPushButton("确定");
    connect(tQpb, &QPushButton::released, this, &MonitorInfoPanel::saveSelection);
    hbox->addWidget(tQpb);
    tQpb=new QPushButton("取消");
    connect(tQpb, &QPushButton::released, this, &QMainWindow::close);
    hbox->addWidget(tQpb);
    
    vbox->addItem(hbox);
    
    QWidget* mainWidget = new QWidget();    
    mainWidget->setLayout(vbox);
    setCentralWidget(mainWidget);
}
void MonitorInfoPanel::getMonitorInfo(){    
    //查询 监测对象配置表 若有记录，配置当前监测房间，人员
    equMonitorObj = EquMonitorObj::get()->selectByPk(bmID);
    if(equMonitorObj!=nullptr){
    
    }
}
void MonitorInfoPanel::saveSelection(){
    //save
    QMap<QString, QString> roomrecordMap;
    roomrecordMap[MonitorRoom::fRoomCode]=roomIDEdit.text();
    QString roomID=MonitorRoom::get()->newRecord(roomrecordMap);
    
    QMap<QString, QString> personrecordMap;
    personrecordMap[MonitorPerson::fPName]=personNameEdit.text();
    QString personID=MonitorPerson::get()->newRecord(personrecordMap);
    
    QMap<QString, QString> EquMonitorObjrecordMap;
    EquMonitorObjrecordMap[EquMonitorObj::fRoomID]=roomID;
    EquMonitorObjrecordMap[EquMonitorObj::fPersonID]=personID;
    EquMonitorObj::get()->newRecord(bmID, EquMonitorObjrecordMap);    
    
    emit ok();
    close();
}
