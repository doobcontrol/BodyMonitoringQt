#include "MonitorInfoPanel.h"
#include "EquMonitorObj.h"
#include "MonitorRoom.h"
#include "MonitorPerson.h"
#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QMessageBox>

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
    roomlistWidget = new QListWidget(this);
    gridLayout->addWidget(roomlistWidget,rowCount,1,1,1);
    roomRowList = MonitorRoom::get()->selectAll();
    for(QMap<QString, QString> roomRow:(*roomRowList)){
        new QListWidgetItem(roomRow[MonitorRoom::fRoomCode], roomlistWidget);
    }
    connect(roomlistWidget, &QListWidget::itemSelectionChanged, this, &MonitorInfoPanel::setRoomFromList);
    
    rowCount++;
    gridLayout->addWidget(new QLabel("姓名："),rowCount,0,1,1);
    gridLayout->addWidget(&personNameEdit,rowCount,1,1,1);    
    
    rowCount++;
    namelistWidget = new QListWidget(this);
    gridLayout->addWidget(namelistWidget,rowCount,1,1,1);
    personRowList = MonitorPerson::get()->selectAll();
    for(QMap<QString, QString> personRow:(*personRowList)){
        new QListWidgetItem(personRow[MonitorPerson::fPName], namelistWidget);
    }
    connect(namelistWidget, &QListWidget::itemSelectionChanged, this, &MonitorInfoPanel::setPersonFromList);
    
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
        monitorRoom = MonitorRoom::get()->selectByPk((*equMonitorObj)[EquMonitorObj::fRoomID]);
        if(monitorRoom!=nullptr){
            roomIDEdit.setText((*monitorRoom)[MonitorRoom::fRoomCode]);
        }
        monitorPerson = MonitorPerson::get()->selectByPk((*equMonitorObj)[EquMonitorObj::fPersonID]);
        if(monitorPerson!=nullptr){
            personNameEdit.setText((*monitorPerson)[MonitorPerson::fPName]);
        }
    }
}
void MonitorInfoPanel::saveSelection(){
    if(roomIDEdit.text().trimmed()=="" || personNameEdit.text().trimmed()==""){
        QMessageBox::critical(this, QString("出错"), QString("房间和姓名均不能为空"));
        return;
    }
    //save
    QString roomID;
    for(QMap<QString, QString> rItem:(*roomRowList)){
        if(rItem[MonitorRoom::fRoomCode]==roomIDEdit.text().trimmed()){
            roomID=rItem[XyKModel::fID];
        }
    }
    if(roomID.isEmpty()){
        QMap<QString, QString> roomrecordMap;
        roomrecordMap[MonitorRoom::fRoomCode]=roomIDEdit.text().trimmed();
        roomID=MonitorRoom::get()->newRecord(roomrecordMap);
    }
    
    QString personID;
    for(QMap<QString, QString> rItem:(*personRowList)){
        if(rItem[MonitorPerson::fPName]==personNameEdit.text().trimmed()){
            personID=rItem[XyKModel::fID];
        }
    }
    if(personID.isEmpty()){
        QMap<QString, QString> personrecordMap;
        personrecordMap[MonitorPerson::fPName]=personNameEdit.text().trimmed();
        personID=MonitorPerson::get()->newRecord(personrecordMap);
    }
    
    QMap<QString, QString> EquMonitorObjrecordMap;
    if(equMonitorObj==nullptr || roomID!=(*equMonitorObj)[EquMonitorObj::fRoomID]){
        EquMonitorObjrecordMap[EquMonitorObj::fRoomID]=roomID;
    }
    if(equMonitorObj==nullptr || personID!=(*equMonitorObj)[EquMonitorObj::fPersonID]){
        EquMonitorObjrecordMap[EquMonitorObj::fPersonID]=personID;
    }
    
    if(EquMonitorObjrecordMap.count()!=0){
        if(equMonitorObj==nullptr){
            EquMonitorObj::get()->newRecord(bmID, EquMonitorObjrecordMap); 
        }
        else{
            EquMonitorObj::get()->updateByPk(bmID, EquMonitorObjrecordMap); 
        }
    }   
    
    emit ok();
    close();
}
void MonitorInfoPanel::setRoomFromList(){
    roomIDEdit.setText(roomlistWidget->currentItem()->text());
}
void MonitorInfoPanel::setPersonFromList(){
    personNameEdit.setText(namelistWidget->currentItem()->text());
}
