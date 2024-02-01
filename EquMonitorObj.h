#pragma once
#include "XyKModel.h"

using namespace XyModel;

class EquMonitorObj: public XyKModel{
//单例模式 静态成员
public:
    static EquMonitorObj* get();
    //字段
    static QString fRoomID;
    static QString fPersonID;
private:
    static EquMonitorObj* defaultInstance;
    static QString realtableCode;

public:
    EquMonitorObj();
protected:
    void createFieldsList();
};
