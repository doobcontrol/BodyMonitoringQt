#pragma once
#include "XyBaseModel.h"
namespace XyModel
{

class XyKModel: public XyBaseModel {

//静态成员
public:
    static QString fID;
private:

//实例成员
public:    
    //查询
    QMap<QString, QString>* selectByPk(const QString& pk); 
       
    //新增
    QString newRecord();
    QString newRecord(const QString& pk);
    QString newRecord(QMap<QString, QString> recordMap);
    QString newRecord(const QString& pk, QMap<QString, QString> recordMap);
    
    //修改    
    void updateOneFieldByPk(const QString& pk, const QString& fieldName, const QString& fieldValue);
    void updateByRowColumn(QMap<QString, QString> recordMap, QMap<QString, QString> fieldMap);
    void updateByPk(const QString& pk, QMap<QString, QString> recordMap);
    
    //删除
    void deleteByPk(const QString& pk);
    void deleteByRow(const QMap<QString, QString> recordMap);
    
protected:
    XyKModel(); 
    virtual void createFieldsList();

};

}
