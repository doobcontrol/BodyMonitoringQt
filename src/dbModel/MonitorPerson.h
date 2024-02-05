#pragma once
#include "XyKModel.h"

using namespace XyModel;

class MonitorPerson: public XyKModel{
//单例模式 静态成员
public:
    static MonitorPerson* get();
    //字段
    static QString fPName;
    static QString fPHoto;
private:
    static MonitorPerson* defaultInstance;
    static QString realtableCode;

public:
    MonitorPerson();
protected:
    void createFieldsList();
};
