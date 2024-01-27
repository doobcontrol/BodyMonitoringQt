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
    
    //修改    
    void updateOneFieldByPk(const QString& pk, const QString& fieldName, const QString& fieldValue);
    
protected:
    XyKModel(); 
    virtual void createFieldsList();

};

}
