#include <QDebug>
#include <QFile>
#include "dbHelper.h"
#include <QSqlError>

using namespace XyModel;

QList<XyModel::XyBaseModel*> dbHelper::initXyBaseModelList;
QSqlDatabase dbHelper::m_db;
QString dbHelper::m_dbType="QSQLITE";
QString dbHelper::m_dbFile="/usr/local/share/BodyMonitoring/bm.db";
void dbHelper::init(){
    
    m_db = QSqlDatabase::addDatabase(m_dbType);
    m_db.setDatabaseName(m_dbFile);
    
    //数据库文件是否存在
    bool isNewDbFile=true;
    if(QFile::exists(m_dbFile)){
    	isNewDbFile=false;
    }
    
    if (!m_db.open())
    {
        qDebug() << "Error: connection with database failed";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
    
    if(isNewDbFile){    
    	//生成数据表    
        for(XyBaseModel* pModel:initXyBaseModelList){       
    	    pModel->createTable();
        }
    }
}
void dbHelper::queryNoReturn(const QString& sqlStr){
    QSqlQuery query;
    query.prepare(sqlStr);
    if(query.exec())
    {
        //success = true;
       //qDebug() << "insertOne" << sqlStr;
    }
    else
    {
        qDebug() << sqlStr;
        qDebug() << "error:"
                 << query.lastError();
    }
}
QMap<QString, QString>* dbHelper::queryRecord(
    const QString& sqlStr, 
    const QList<QMap<QString, QString>>& FieldsList)
{
    QSqlQuery query(sqlStr);
    QMap<QString, QString> *retQMap=new QMap<QString, QString>;
    if(query.first())
    {    
        for(QMap<QString, QString> fQMap:FieldsList){           
            retQMap->insert(fQMap[XyBaseModel::FieldCode], query.value(fQMap[XyBaseModel::FieldCode]).toString());
        }
    }
    else
    {
        qDebug() << sqlStr;
        qDebug() << "error:"
                << query.lastError();
    }
    return retQMap;
}
QList<QMap<QString, QString>>* dbHelper::queryRecords(
    const QString& sqlStr, 
    const QList<QMap<QString, QString>>& FieldsList)
{
    QSqlQuery query(sqlStr);
    QList<QMap<QString, QString>>* retList=new QList<QMap<QString, QString>>;
    while (query.next())
    {    
        QMap<QString, QString> tQMap;    
         
        for(QMap<QString, QString> fQMap:FieldsList){           
            tQMap[fQMap[XyBaseModel::FieldCode]]=query.value(fQMap[XyBaseModel::FieldCode]).toString();
        }
    
        retList->append(tQMap);
    }
    return retList;
}
