#include "XyKModel.h"
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
QMap<QString, QString>* XyKModel::selectByPk(const QString& pk){
    QSqlQuery query(QString("SELECT * FROM %1 where %2='%3'").arg(tableCode).arg(fID).arg(pk));
    QMap<QString, QString> *retQMap=new QMap<QString, QString>;
    if(query.first())
    {    
        for(QMap<QString, QString> fQMap:FieldsList){           
            retQMap->insert(fQMap[FieldCode], query.value(fQMap[FieldCode]).toString());
        }
    }
    else{
        qDebug() << "selectByPk error:"
                 << query.lastError();
    }
    return retQMap;
}
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
void XyKModel::updateOneFieldByPk(const QString& pk, const QString& fieldCode, const QString& fieldValue){ //slot
   QString setStr(QString("%1 = '%2'").arg(fieldCode).arg(fieldValue));
   QString whereStr(QString("%1 = '%2'").arg(fID).arg(pk));
   QString sqlStr=QString("UPDATE %1 SET %2 WHERE %3").arg(tableCode).arg(setStr).arg(whereStr);
   
   QSqlQuery query;
   query.prepare(sqlStr);
   if(query.exec())
   {
       //success = true;
       //qDebug() << "update:" << sqlStr;
   }
   else
   {
       qDebug() << "update error:"
       << sqlStr;
       //qDebug() << "insertOne error:"
       //         << query.lastError()
   }
}
void XyKModel::updateByRowColumn(const QMap<QString, QString> recordMap, const QMap<QString, QString> fieldMap){
    QString pk=recordMap[fID]; 
    QString fieldCode=fieldMap[FieldCode]; 
    QString fieldValue=recordMap[fieldCode];
    updateOneFieldByPk(pk, fieldCode, fieldValue);
}
