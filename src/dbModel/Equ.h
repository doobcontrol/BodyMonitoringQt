#pragma once
#include "XyKModel.h"

using namespace XyModel;

class Equ: public XyKModel{
//单例模式 静态成员
public:
    static Equ* get();
    static QString fEquID;
    static QString fEquRoom;
private:
    static Equ* defaultInstance;
    static QString realtableCode;

public:
    Equ();
protected:
    void createFieldsList();
};
