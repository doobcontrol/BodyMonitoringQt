#include "bmRecord.h"
#include "EquMonitorObj.h"
#include "MonitorRoom.h"
#include "MonitorPerson.h"
#include <QDebug>
#include <QSqlError>


using namespace XyModel;

//单例模式 静态成员
bmRecord* bmRecord::defaultInstance = nullptr;
bmRecord* bmRecord::get(){
    if(defaultInstance == nullptr){
    	defaultInstance = new bmRecord();
    }
    return defaultInstance;
}
QString bmRecord::realtableCode="bmRecord";
QString bmRecord::fEquID("fEquID");
QString bmRecord::fRoomID("fRoomID");
QString bmRecord::fPersonID("fPersonID");
QString bmRecord::fStartTimeID("fStartTimeID");
QString bmRecord::fStopTimeID("fStopTimeID");

bmRecord::bmRecord():XyKModel() {
    tableCode=realtableCode;
    createFieldsList();
}
void bmRecord::createFieldsList(){
    XyKModel::createFieldsList();
    addAField("设备ID",fEquID,DataType_text,"50","0");  
    addAField("房间ID",fRoomID,DataType_text,"50","0");  
    addAField("人员ID",fPersonID,DataType_text,"50","0");  
    addAField("开始时间",fStartTimeID,DataType_text,"50","0");  
    addAField("人员ID",fStopTimeID,DataType_text,"50","0");  
    ForeignKeyMap[fEquID]=EquMonitorObj::get()->getTableCode();
    ForeignKeyMap[fRoomID]=MonitorRoom::get()->getTableCode();
    ForeignKeyMap[fPersonID]=MonitorPerson::get()->getTableCode();
}
