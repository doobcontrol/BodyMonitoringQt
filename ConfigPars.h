#pragma once
#include "XyKModel.h"

using namespace XyModel;

class ConfigPars: public XyKModel{
//单例模式 静态成员
public:
    static ConfigPars* get();
    //字段
    static QString fParValue;
    
    //其它常量
    static QString HeartRateMax;
    static QString HeartRateMin;
    static QString BreatheMax;
    static QString BreatheMin;
    
private:
    static ConfigPars* defaultInstance;
    static QString realtableCode;

public:
    ConfigPars();
    QString getValue(QString pName);
    void setValue(QString pName, QString pValue);
private:
    void addInitRecord(QString pName, QString pValue);
    QMap<QString, QString>* pvMap=nullptr;
    void createPvMap();
protected:
    void createFieldsList();
};
