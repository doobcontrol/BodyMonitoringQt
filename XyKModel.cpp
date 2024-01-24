#include "XyKModel.h"
#include <QDebug>

using namespace XyModel;

//静态成员
QString XyKModel::fID("fID");
    
XyKModel::XyKModel():XyBaseModel() {
}
void XyKModel::createFieldsList(){
    XyBaseModel::createFieldsList();
    addAField("pkID",fID,DataType_text,"50","1");    
}
