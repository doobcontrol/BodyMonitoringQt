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
    XyKModel();    
protected:
    virtual void createFieldsList();

};

}
