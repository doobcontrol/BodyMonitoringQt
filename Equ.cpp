#include "Equ.h"
#include <QDebug>
#include <QSqlError>


using namespace XyModel;

//单例模式 静态成员
Equ* Equ::defaultInstance = nullptr;
Equ* Equ::get(){
    if(defaultInstance == nullptr){
    	defaultInstance = new Equ();
    }
    return defaultInstance;
}
QString Equ::realtableCode="Equ";
QString Equ::fEquID("fEquID");
QString Equ::fEquRoom("fEquRoom");

Equ::Equ():XyKModel() {
    tableCode=realtableCode;
    createFieldsList();
}
void Equ::createFieldsList(){
    XyKModel::createFieldsList();
    addAField("设备ID",fEquID,DataType_text,"50","0");  
    addAField("房间号",fEquRoom,DataType_text,"500","0");  
}
