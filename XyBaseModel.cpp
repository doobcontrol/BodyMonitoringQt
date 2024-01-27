#include "dbHelper.h"
#include "XyBaseModel.h"
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
    
XyBaseModel::XyBaseModel() {
    //createFieldsList();
}
QList<QMap<QString, QString>> FieldsList;
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
    
    QString sqlStr=QString("create table  %1 (%2)").arg(tableCode).arg(fieldStr);
    
    dbHelper::queryNoReturn(sqlStr);
}

QList<QMap<QString, QString>>* XyBaseModel::selectAll(){
    QString sqlStr = QString("SELECT * FROM %1").arg(tableCode);
    return dbHelper::queryRecords(sqlStr, FieldsList);
}

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
