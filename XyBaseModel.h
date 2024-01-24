#pragma once
#include <QList>
#include <QMap>
#include "dbHelper.h"

namespace XyModel
{

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
    void createTable(); 
    
protected:
    XyBaseModel();
    QString tableCode;   //表物理名（数据库操作名）
    virtual void createFieldsList();
    QList<QMap<QString, QString>> FieldsLis;
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
