#pragma once
#include "XyKModel.h"

using namespace XyModel;

class bmRecordItem: public XyKModel{
//单例模式 静态成员
public:
    static bmRecordItem* get();
    //字段
    static QString fRecordID;
    static QString fTimeID;
    static QString fBreathe;
    static QString fHeartRate;
private:
    static bmRecordItem* defaultInstance;
    static QString realtableCode;

public:
    bmRecordItem();
    QList<QMap<QString, QString>>* selectItemByRecord(QString RecordID); 
protected:
    void createFieldsList();
};
