#pragma once
#include <QSqlDatabase>
#include <QSqlQuery>
#include "XyKModel.h"

using namespace XyModel;

class dbHelper {
public:
    static void init(QString workDb);
    static QList<XyModel::XyBaseModel*> initXyBaseModelList;
    static void queryNoReturn(const QString& sqlStr);
    static QMap<QString, QString>* queryRecord(const QString& sqlStr); 
    static QList<QMap<QString, QString>>* queryRecords(const QString& sqlStr); 
private:
    static QSqlDatabase m_db;
    static QString m_dbType;
    static QString m_dbFile;
};
