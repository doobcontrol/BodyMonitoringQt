#include "XyKModel.h"
#include "dbHelper.h"
#include <QDebug>
#include <QUuid>
#include <QSqlError>

using namespace XyModel;

//静态成员
QString XyKModel::fID("fID");
    
XyKModel::XyKModel():XyBaseModel() {
}
void XyKModel::createFieldsList(){
    XyBaseModel::createFieldsList();
    addAField("pkID",fID,DataType_text,"50","1");    
}
//查询
QMap<QString, QString>* XyKModel::selectByPk(const QString& pk){
    QString sqlStr = QString("SELECT * FROM %1 where %2='%3'").arg(tableCode).arg(fID).arg(pk);
    return dbHelper::queryRecord(sqlStr);
}

//新增
QString XyKModel::newRecord(){
    QString pk(QUuid::createUuid().toString(QUuid::Id128));
    newRecord(pk);
    return pk;
}
QString XyKModel::newRecord(const QString& pk){
    QMap<QString, QString> recordMap;
    recordMap[fID]=pk;
    insertOne(recordMap);
    return pk;
}
QString XyKModel::newRecord(QMap<QString, QString> recordMap){
    QString pk(QUuid::createUuid().toString(QUuid::Id128));
    newRecord(pk, recordMap);
    return pk;
}
QString XyKModel::newRecord(const QString& pk, QMap<QString, QString> recordMap){
    recordMap[fID]=pk;
    insertOne(recordMap);
    return pk;
}

//修改
void XyKModel::updateOneFieldByPk(const QString& pk, const QString& fieldCode, const QString& fieldValue){ //slot
   QString setStr(QString("%1 = '%2'").arg(fieldCode).arg(fieldValue));
   QString whereStr(QString("%1 = '%2'").arg(fID).arg(pk));
   QString sqlStr=QString("UPDATE %1 SET %2 WHERE %3").arg(tableCode).arg(setStr).arg(whereStr);
   
   dbHelper::queryNoReturn(sqlStr);
}
void XyKModel::updateByRowColumn(const QMap<QString, QString> recordMap, const QMap<QString, QString> fieldMap){
    QString pk=recordMap[fID]; 
    QString fieldCode=fieldMap[FieldCode]; 
    QString fieldValue=recordMap[fieldCode];
    updateOneFieldByPk(pk, fieldCode, fieldValue);
}
void XyKModel::updateByPk(const QString& pk, QMap<QString, QString> recordMap){
   QString setStr;
   for(QString key:recordMap.keys()){
       if(!setStr.isEmpty()){
           setStr.append(QString(","));
       }
       setStr.append(QString("%1 = '%2'").arg(key).arg(recordMap[key]));
   }
   
   QString whereStr(QString("%1 = '%2'").arg(fID).arg(pk));   
   QString sqlStr=QString("UPDATE %1 SET %2 WHERE %3").arg(tableCode).arg(setStr).arg(whereStr);
   
   dbHelper::queryNoReturn(sqlStr);
}

//删除
void XyKModel::deleteByPk(const QString& pk){
    QString sqlStr=QString("DELETE FROM %1 WHERE %2 = '%3'").arg(tableCode).arg(fID).arg(pk);
   
    dbHelper::queryNoReturn(sqlStr);
}
void XyKModel::deleteByRow(const QMap<QString, QString> recordMap){
    deleteByPk(recordMap[fID]);
}
