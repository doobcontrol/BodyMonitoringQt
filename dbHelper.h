#pragma once
#include <QSqlDatabase>
#include <QSqlQuery>

class dbHelper {
public:
    static void init();
    static void queryNoReturn(const QString& sqlStr);
private:
    static QSqlDatabase m_db;
    static QString m_dbType;
    static QString m_dbFile;
};
