#include "dbHelper.h"
#include "XyBaseModel.h"
#include "XyKModel.h"
#include <QDebug>

using namespace XyModel;

//单例模式 静态成员
QString XyBaseModel::FieldName("FieldName");
QString XyBaseModel::FieldCode("FieldCode");
QString XyBaseModel::DataType("DataType");
QString XyBaseModel::DataType_text("text");
QString XyBaseModel::DataType_int("int");
QString XyBaseModel::DataType_float("float");
QString XyBaseModel::DataType_date("date");
QString XyBaseModel::DataLength("DataLength");
QString XyBaseModel::IsPrimaryKey("IsPrimaryKey");

//实例成员
XyBaseModel::XyBaseModel() {
    //createFieldsList();
}
QString XyBaseModel::getTableCode(){
    return tableCode;
}
void XyBaseModel::createFieldsList(){
}
void XyBaseModel::addAField(
        const QString& fFieldName,
        const QString& fFieldCode,
        const QString& fDataType,
        const QString& fDataLength,
        const QString& fIsPrimaryKey
    )
{
    QMap<QString, QString> tQMap;    
    tQMap[FieldName]=fFieldName;
    tQMap[FieldCode]=fFieldCode;
    tQMap[DataType]=fDataType;
    tQMap[DataLength]=fDataLength;
    tQMap[IsPrimaryKey]=fIsPrimaryKey;
    
    FieldsList.append(tQMap);
}

void XyBaseModel::createTable(){

    QString fieldStr=QString("");    
    for(QMap<QString, QString> tQMap:FieldsList){    
    	if(!fieldStr.isEmpty()){
    	    fieldStr.append(",");
    	}
    	
    	QString dtStr;
    	if(tQMap[DataType]==DataType_text){
    	    dtStr=QString(" VARCHAR(%1)").arg(tQMap[DataLength]);
    	}
    	else if(tQMap[DataType]==DataType_int){
    	    dtStr=QString(" INT");
    	}
    	else if(tQMap[DataType]==DataType_float){
    	    dtStr=QString(" FLOAT");
    	}
    	else if(tQMap[DataType]==DataType_date){
    	    dtStr=QString(" DATE");
    	}
    	
    	fieldStr.append(QString("%1 %2").arg(tQMap[FieldCode]).arg(dtStr));
    	
    	if(tQMap[IsPrimaryKey]=="1"){
    	    fieldStr.append(QString(" primary key"));
    	}
    }
    	
    //根据数据库类型判断是否一生成表的同时生成外键。
    //（如，对SQlite. 要先关闭外键功能 PRAGMA foreign_keys = OFF;对其它数据库，以免循环引用问题，全部表建完后再建外键）
    for(QString key:ForeignKeyMap.keys()){    
    	fieldStr.append(QString(",  FOREIGN KEY(%1) REFERENCES %2(%3)")
    	    .arg(key)
    	    .arg(ForeignKeyMap[key]->getTableCode())
    	    .arg(XyKModel::fID)
    	    );
    }
    
    QString sqlStr=QString("create table  %1 (%2)").arg(tableCode).arg(fieldStr);
    
    dbHelper::queryNoReturn(sqlStr);
}
void XyBaseModel::createInitRecords(){
    insertRecordsList(InitRecordsList);
}

//查询
QString XyBaseModel::selectAllstr(){
    return QString("SELECT * FROM %1").arg(tableCode);
}
QList<QMap<QString, QString>>* XyBaseModel::selectAll(){
    return dbHelper::queryRecords(selectAllstr());
}
QList<QMap<QString, QString>>* XyBaseModel::selectByWhereString(QString whereString){
    QString sqlStr = QString("%1 WHERE %2").arg(selectAllstr()).arg(whereString);
    return dbHelper::queryRecords(sqlStr);
}
QString XyBaseModel::selectAllLjstr(){
    //tempSql += " select " + tableCode + ".*" + addSelectString + " from " + tableCode + leftJoinString;
    LjInfo ljInfo;
    createLjInfo(ljInfo);
    QString sqlStr = QString("SELECT %1.* %2 FROM %1 %3")
        .arg(tableCode)
        .arg(ljInfo.asStr)
        .arg(ljInfo.ljStr);
    
    return sqlStr;
}
void XyBaseModel::createLjInfo(LjInfo& ljInfo){
    for(QString fieldCode:ForeignKeyMap.keys()){
        QString leftJoinTablePro=QString("%1%2")
                    .arg(ForeignKeyMap[fieldCode]->getTableCode())
                    .arg(fieldCode);
        QString addSelectString;
        for(QMap<QString, QString> fMap:ForeignKeyMap[fieldCode]->FieldsList){
            if(fMap[FieldCode]!=XyKModel::fID){
                addSelectString.append(
                    QString(",%1.%2  %3%2")
                    .arg(leftJoinTablePro)
                    .arg(fMap[FieldCode])
                    .arg(fieldCode)
                );
            }
        }
        if(!addSelectString.isEmpty()){
            ljInfo.asStr.append(addSelectString);
            ljInfo.ljStr.append(QString(" left join %1 %2 on %3.%4=%2.%5")
                .arg(ForeignKeyMap[fieldCode]->getTableCode())
                .arg(leftJoinTablePro)
                .arg(tableCode)    
                .arg(fieldCode)     
                .arg(XyKModel::fID)                
            );
        }
    }
}
QList<QMap<QString, QString>>* XyBaseModel::selectAllLj(){
    return dbHelper::queryRecords(selectAllLjstr());
}
QList<QMap<QString, QString>>* XyBaseModel::selectAllLjByWhereString(QString whereString){
    QString sqlStr = QString("%1 WHERE %2").arg(selectAllLjstr()).arg(whereString);
    return dbHelper::queryRecords(sqlStr);
}
QList<QMap<QString, QString>>* XyBaseModel::selectByOneField(QString fName, QString fValue){
    QString whereString=QString("%1='%2'")
        .arg(fName)
        .arg(fValue)
    ;
    return selectByWhereString(whereString);
}

//新增
void XyBaseModel::insertOne(const QMap<QString, QString>& recordMap){
   QString fieldsStr("");
   QString valuesStr("");
   for(QString key:recordMap.keys()){ 
    	if(!fieldsStr.isEmpty()){
    	    fieldsStr.append(",");
    	    valuesStr.append(",");
    	}
    	fieldsStr.append(key);
    	valuesStr.append(QString("'%1'").arg(recordMap[key]));
   }
   QString sqlStr=QString("INSERT INTO %1 (%2) VALUES (%3)").arg(tableCode).arg(fieldsStr).arg(valuesStr);
   
   dbHelper::queryNoReturn(sqlStr);
}
void XyBaseModel::insertRecordsList(const QList<QMap<QString, QString>>& RecordsList){
    for(QMap<QString, QString> recordMap:RecordsList){
        insertOne(recordMap);
    }
}
