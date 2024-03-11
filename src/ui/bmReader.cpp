#include <QByteArray>
#include <QtSerialPort>
#include <QSerialPortInfo>

#include "bmReader.h"
bmReader::bmReader(QObject *parent): QThread(parent){}
void bmReader::run() {
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    
    QSerialPort serial;
    bool openSucceed=false;
    QString openErroStr("连接设备失败，请检查是否已正确连接！");
    for (const QSerialPortInfo &portInfo : serialPortInfos) {
    	serial.setPort(portInfo);
        if (serial.open(QIODevice::ReadWrite)) {
            openSucceed=true;
            break;
        }
        else{
            openErroStr=QString("串口失败：%1").arg(serial.errorString());
        }
    }
    if (!openSucceed) {
        emit serialPortErro(openErroStr);
        emit finished();
        return;
    }   
    
    serial.setBaudRate(QSerialPort::Baud38400);
    serial.setDataBits(QSerialPort::Data8);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setParity(QSerialPort::NoParity);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    
    serial.setDataTerminalReady(true);
    serial.clear();
    QByteArray readBytes;
    
    QThread::sleep(1); 
    while(!this->isInterruptionRequested()){
 	serial.waitForReadyRead(); //must
 	if(serial.bytesAvailable()<16){
 	    continue;
 	}
 	readBytes.clear();
    	readBytes=serial.readAll();
   	
	if(!readBytes.isEmpty()){	
	    if(checkPkgValid(readBytes)){
		emit bmDataGot(
			getBmID(readBytes),
			int(readBytes[9]),
			readBytes[10] * 256 + readBytes[11]
		);
	    }
	    else{
	    	//emit serialPortErro(QString("设备识别中……(%1)").arg(readBytes.toHex(':')));
	    	emit serialPortErro(QString("设备识别中……"));
	    	//重新连接。解决断开后常常保持一直（设备识别中……）状态的问题。很可能是设备需要复位。而重新连接起到了此作用
	    	serial.close();
	    	serial.open(QIODevice::ReadWrite);
	    }
	}
	else{
	    emit serialPortErro(QString("接收失败：%1").arg(serial.errorString()));
	    break;
	} 
    }
   
    serial.close();
    emit finished();
}
bool bmReader::checkPkgValid(const QByteArray &bmDataPkg){
    bool retBl=true;
    if(bmDataPkg[0]!=char(0x55)){
        retBl=false;
    }
    if(bmDataPkg[1]!=char(0xaa)){
        retBl=false;
    }
    if(bmDataPkg[2]!=char(0x03)){
        retBl=false;
    }
    if(bmDataPkg[14]!=char(0x0d)){
        retBl=false;
    }
    if(bmDataPkg[15]!=char(0x0a)){
        retBl=false;
    }
    return retBl;
}
QString bmReader::getBmID(const QByteArray &bmDataPkg){
    return charToHexStr(bmDataPkg[3])
    	+ charToHexStr(bmDataPkg[4])
    	+ charToHexStr(bmDataPkg[5])
    	+ charToHexStr(bmDataPkg[6])
    	+ charToHexStr(bmDataPkg[7])
    	+ charToHexStr(bmDataPkg[8])
    	;
}
QString bmReader::charToHexStr(char chr){
    return QString("%1").arg(chr, 2, 16, QLatin1Char('0')).toUpper().right(2);
}
