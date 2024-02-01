#include "MonitorPerson.h"
#include <QDebug>
#include <QSqlError>


using namespace XyModel;

//单例模式 静态成员
MonitorPerson* MonitorPerson::defaultInstance = nullptr;
MonitorPerson* MonitorPerson::get(){
    if(defaultInstance == nullptr){
    	defaultInstance = new MonitorPerson();
    }
    return defaultInstance;
}
QString MonitorPerson::realtableCode="MonitorPerson";
QString MonitorPerson::fPName("fPName");
QString MonitorPerson::fPHoto("fPHoto");

MonitorPerson::MonitorPerson():XyKModel() {
    tableCode=realtableCode;
    createFieldsList();
}
void MonitorPerson::createFieldsList(){
    XyKModel::createFieldsList();
    addAField("姓名",fPName,DataType_text,"50","0");  
    addAField("照片",fPHoto,DataType_text,"1000","0");  
}
