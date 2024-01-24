#include <QDebug>
#include <QFile>
#include "XyBaseModel.h"
#include "XyKModel.h"
#include "Equ.h"
#include "dbHelper.h"
#include <QSqlError>

using namespace XyModel;

QSqlDatabase dbHelper::m_db;
QString dbHelper::m_dbType="QSQLITE";
QString dbHelper::m_dbFile="bm.db";
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
    	XyBaseModel* bmodel=Equ::get();
    	
    	bmodel->createTable();
    }
}
void dbHelper::queryNoReturn(const QString& sqlStr){
    QSqlQuery query;
    if (query.exec(sqlStr))
    {
        qDebug() << QString("create table ok: %1").arg(sqlStr);
    }
    else
    {
        qDebug() << "create table Error: " + query.lastError().text();
        qDebug() << QString("Erro sql String: %1").arg(sqlStr);
    }
}
