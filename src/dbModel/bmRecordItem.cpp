#include "bmRecordItem.h"
#include "bmRecord.h"
#include <QDebug>
#include <QSqlError>


using namespace XyModel;

//单例模式 静态成员
bmRecordItem* bmRecordItem::defaultInstance = nullptr;
bmRecordItem* bmRecordItem::get(){
    if(defaultInstance == nullptr){
    	defaultInstance = new bmRecordItem();
    }
    return defaultInstance;
}
QString bmRecordItem::realtableCode="bmRecordItem";
QString bmRecordItem::fRecordID("fRecordID");
QString bmRecordItem::fTimeID("fTimeID");
QString bmRecordItem::fBreathe("fBreathe");
QString bmRecordItem::fHeartRate("fHeartRate");

bmRecordItem::bmRecordItem():XyKModel() {
    tableCode=realtableCode;
    createFieldsList();
}
void bmRecordItem::createFieldsList(){
    XyKModel::createFieldsList();
    addAField("记录ID",fRecordID,DataType_text,"50","0");  
    addAField("时间",fTimeID,DataType_text,"50","0"); 
    addAField("呼吸",fBreathe,DataType_text,"50","0");  
    addAField("心跳",fHeartRate,DataType_text,"50","0");   
    ForeignKeyMap[fRecordID]=bmRecord::get();
}
QList<QMap<QString, QString>>* bmRecordItem::selectItemByRecord(QString RecordID){
    return selectByOneField(fRecordID, RecordID);
}
