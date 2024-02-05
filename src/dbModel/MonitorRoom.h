#pragma once
#include "XyKModel.h"

using namespace XyModel;

class MonitorRoom: public XyKModel{
//单例模式 静态成员
public:
    static MonitorRoom* get();
    //字段
    static QString fRoomCode;
private:
    static MonitorRoom* defaultInstance;
    static QString realtableCode;

public:
    MonitorRoom();
protected:
    void createFieldsList();
};
