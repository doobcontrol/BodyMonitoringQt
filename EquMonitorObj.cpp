#include "EquMonitorObj.h"
#include "MonitorRoom.h"
#include "MonitorPerson.h"
#include <QDebug>
#include <QSqlError>


using namespace XyModel;

//单例模式 静态成员
EquMonitorObj* EquMonitorObj::defaultInstance = nullptr;
EquMonitorObj* EquMonitorObj::get(){
    if(defaultInstance == nullptr){
    	defaultInstance = new EquMonitorObj();
    }
    return defaultInstance;
}
QString EquMonitorObj::realtableCode="EquMonitorObj";
QString EquMonitorObj::fRoomID("fRoomID");
QString EquMonitorObj::fPersonID("fPersonID");

EquMonitorObj::EquMonitorObj():XyKModel() {
    tableCode=realtableCode;
    createFieldsList();
}
void EquMonitorObj::createFieldsList(){
    XyKModel::createFieldsList();
    addAField("房间ID",fRoomID,DataType_text,"50","0");  
    addAField("人员ID",fPersonID,DataType_text,"50","0");  
    ForeignKeyMap[fRoomID]=MonitorRoom::get()->getTableCode();
    ForeignKeyMap[fPersonID]=MonitorPerson::get()->getTableCode();
}
