#include "MonitorRoom.h"
#include <QDebug>
#include <QSqlError>


using namespace XyModel;

//单例模式 静态成员
MonitorRoom* MonitorRoom::defaultInstance = nullptr;
MonitorRoom* MonitorRoom::get(){
    if(defaultInstance == nullptr){
    	defaultInstance = new MonitorRoom();
    }
    return defaultInstance;
}
QString MonitorRoom::realtableCode="MonitorRoom";
QString MonitorRoom::fRoomCode("fRoomCode");

MonitorRoom::MonitorRoom():XyKModel() {
    tableCode=realtableCode;
    createFieldsList();
}
void MonitorRoom::createFieldsList(){
    XyKModel::createFieldsList();
    addAField("房间号",fRoomCode,DataType_text,"50","0");
}
