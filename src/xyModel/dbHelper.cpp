#include <QDebug>
#include <QFile>
#include "dbHelper.h"
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>

using namespace XyModel;

QList<XyModel::XyBaseModel*> dbHelper::initXyBaseModelList;
QSqlDatabase dbHelper::m_db;
QString dbHelper::m_dbType="QSQLITE";
QString dbHelper::m_dbFile="bm.db";
void dbHelper::init(QString workDb){
    m_dbFile=workDb;
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
        qDebug() << QString("m_dbFile: %1").arg(m_dbFile);
        return;
    }
    
    if(isNewDbFile){    
    	//生成数据表    
        for(XyBaseModel* pModel:initXyBaseModelList){       
    	    pModel->createTable();
        }
        
        //生成模型配置的初始数据 
        for(XyBaseModel* pModel:initXyBaseModelList){       
    	    pModel->createInitRecords();
        }
        
        //生成外键
        
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
QMap<QString, QString>* dbHelper::queryRecord(const QString& sqlStr)
{
    QSqlQuery query;
    query.prepare(sqlStr);
    QMap<QString, QString> *retQMap=nullptr;
    if(query.exec())
    {
        if(query.first())
        {    
            retQMap=new QMap<QString, QString>;
            QSqlRecord rec = query.record();
            int recordCount = rec.count();
            for(int i=0;i<recordCount;i++){
                retQMap->insert(rec.field(i).name(), rec.value(i).toString());
            }
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
QList<QMap<QString, QString>>* dbHelper::queryRecords(const QString& sqlStr)
{
    QSqlQuery query;
    query.prepare(sqlStr);
    QList<QMap<QString, QString>>* retList=new QList<QMap<QString, QString>>;
    if(query.exec())
    {
        while (query.next())
        {    
            QSqlRecord rec = query.record();
            int recordCount = rec.count();
            QMap<QString, QString> tQMap;   
            for(int i=0;i<recordCount;i++){
                tQMap[rec.field(i).name()]=rec.value(i).toString(); 
            }
            retList->append(tQMap);
        }
    }
    else
    {
        qDebug() << sqlStr;
        qDebug() << "error:"
                 << query.lastError();
    }
    return retList;
}
