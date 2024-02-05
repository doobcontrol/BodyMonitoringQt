#pragma once
#include "XyKModel.h"

using namespace XyModel;

class bmRecord: public XyKModel{
//单例模式 静态成员
public:
    static bmRecord* get();
    //字段
    static QString fEquID;
    static QString fRoomID;
    static QString fPersonID;
    static QString fStartTimeID;
    static QString fStopTimeID;
private:
    static bmRecord* defaultInstance;
    static QString realtableCode;

public:
    bmRecord();
protected:
    void createFieldsList();
};
