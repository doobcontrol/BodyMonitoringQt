#include "ConfigPars.h"
#include <QDebug>
#include <QSqlError>


using namespace XyModel;

//单例模式 静态成员
ConfigPars* ConfigPars::defaultInstance = nullptr;
ConfigPars* ConfigPars::get(){
    if(defaultInstance == nullptr){
    	defaultInstance = new ConfigPars();
    }
    return defaultInstance;
}
QString ConfigPars::realtableCode="ConfigPars";
QString ConfigPars::fParValue("fParValue");
//其它常量
QString ConfigPars::HeartRateMax("HeartRateMax");
QString ConfigPars::HeartRateMin("HeartRateMin");
QString ConfigPars::BreatheMax("BreatheMax");
QString ConfigPars::BreatheMin("BreatheMin");

ConfigPars::ConfigPars():XyKModel() {
    tableCode=realtableCode;
    createFieldsList();
}
void ConfigPars::createFieldsList(){
    XyKModel::createFieldsList();
    addAField("参数值",fParValue,DataType_text,"1000","0");
    
    //初始值
    addInitRecord(HeartRateMax,QString("100"));
    addInitRecord(HeartRateMin,QString("40"));
    addInitRecord(BreatheMax,QString("25"));
    addInitRecord(BreatheMin,QString("8"));
}
void ConfigPars::addInitRecord(QString pName, QString pValue){
    QMap<QString, QString> recordMap;
    recordMap[XyKModel::fID]=pName;
    recordMap[fParValue]=pValue;
    InitRecordsList.append(recordMap);
}
void ConfigPars::createPvMap(){
    pvMap=new QMap<QString, QString>;
    QList<QMap<QString, QString>>* pList=get()->selectAll();
    for(QMap<QString, QString> pMap:(*pList)){
        (*pvMap)[pMap[fID]]=pMap[fParValue];
    }
}
QString ConfigPars::getValue(QString pName){
    if(pvMap==nullptr){
        createPvMap();
    }
    return (*pvMap)[pName];
}
void ConfigPars::setValue(QString pName, QString pValue){
    if(pvMap==nullptr){
        createPvMap();
    }
    (*pvMap)[pName]=pValue;
    updateOneFieldByPk(pName,fParValue,pValue);
}
