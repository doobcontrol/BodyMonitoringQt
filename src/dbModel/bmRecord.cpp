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
    addAField("结束时间",fStopTimeID,DataType_text,"50","0");  
    ForeignKeyMap[fEquID]=EquMonitorObj::get();
    ForeignKeyMap[fRoomID]=MonitorRoom::get();
    ForeignKeyMap[fPersonID]=MonitorPerson::get();
}

//查询
QList<QMap<QString, QString>>* bmRecord::selectByStartDate(QDate startDate){
    QString startTimeString=QString("%1 00:00:0.000").arg(startDate.toString("yyyy-MM-dd"));
    QString endTimeString=QString("%1 00:00:0.000").arg((startDate.addDays(1)).toString("yyyy-MM-dd"));
    QString whereString=QString("%1>='%2' AND %3<='%4'")
        .arg(fStartTimeID)
        .arg(startTimeString)
        .arg(fStartTimeID)
        .arg(endTimeString)
    ;
    
    return selectAllLjByWhereString(whereString);
} 
