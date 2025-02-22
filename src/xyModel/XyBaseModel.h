#pragma once
#include <QList>
#include <QMap>

namespace XyModel
{
//Include headers with crossed references
class XyBaseModel;
typedef class XyBaseModel XyBaseModel;
}
#include "XyKModel.h"

namespace XyModel
{

struct LjInfo  
{  
    QString asStr; //addSelectString
    QString ljStr; //leftJoinString
};

class XyBaseModel {
//静态成员
public:
    static QString FieldName;
    static QString FieldCode;
    static QString DataType;
    static QString DataType_text;
    static QString DataType_int;
    static QString DataType_float;
    static QString DataType_date;
    static QString DataLength;
    static QString IsPrimaryKey;
private:

//实例成员
public:   
    QList<QMap<QString, QString>> FieldsList;
    QMap<QString, XyKModel*> ForeignKeyMap;
    QList<QMap<QString, QString>> InitRecordsList;
    void createTable();
    QString getTableCode();
    void createInitRecords();
    
    //查询
    QString selectAllstr(); 
    QList<QMap<QString, QString>>* selectAll(); 
    QList<QMap<QString, QString>>* selectByWhereString(QString whereString); 
    QString selectAllLjstr();
    void createLjInfo(LjInfo& ljInfo);
    QList<QMap<QString, QString>>* selectAllLj(); 
    QList<QMap<QString, QString>>* selectAllLjByWhereString(QString whereString); 
    QList<QMap<QString, QString>>* selectByOneField(QString fName, QString fValue); 
    
    //新增
    void insertOne(const QMap<QString, QString>& recordMap);
    void insertRecordsList(const QList<QMap<QString, QString>>& RecordsList);
    
protected:
    XyBaseModel();
    QString tableCode;   //表物理名（数据库操作名）
    virtual void createFieldsList();
    void addAField(
        const QString& fFieldName,
        const QString& fFieldCode,
        const QString& fDataType,
        const QString& fDataLength,
        const QString& fIsPrimaryKey
    );
private:

};

}
