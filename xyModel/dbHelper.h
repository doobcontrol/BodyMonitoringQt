#pragma once
#include <QSqlDatabase>
#include <QSqlQuery>
#include "XyKModel.h"

using namespace XyModel;

class dbHelper {
public:
    static void init();
    static QList<XyModel::XyBaseModel*> initXyBaseModelList;
    static void queryNoReturn(const QString& sqlStr);
    static QMap<QString, QString>* queryRecord(
        const QString& sqlStr, 
        const QList<QMap<QString, QString>>& FieldsList); 
    static QList<QMap<QString, QString>>* queryRecords(
        const QString& sqlStr, 
        const QList<QMap<QString, QString>>& FieldsList); 
private:
    static QSqlDatabase m_db;
    static QString m_dbType;
    static QString m_dbFile;
};
