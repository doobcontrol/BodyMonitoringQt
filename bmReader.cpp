#include <QByteArray>
#include <QtSerialPort>
#include <QSerialPortInfo>

#include "bmReader.h"

void bmReader::run() {
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    //const QSerialPortInfo &portInfo = serialPortInfos[0];  
    
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
        return;
    }   
    
    serial.setBaudRate(QSerialPort::Baud38400);
    serial.setDataBits(QSerialPort::Data8);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setParity(QSerialPort::NoParity);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    
    //int i=0;
    while(1){
    	//emit serialPortErro(QString("准备读取……"));
 	serial.waitForReadyRead(); //must
    	QByteArray readBytes=serial.readAll();//read(16);
   	
 	//out << QString(" 字节数: %1").arg(readBytes.size()) << Qt::endl;
	if(!readBytes.isEmpty()){	
		emit bmDataGot(
			getBmID(readBytes),
			int(readBytes[9]),
			readBytes[10] * 256 + readBytes[11]
		);
	}
	else{
	    emit serialPortErro(QString("接收失败：%1").arg(serial.errorString()));
	    //out << QString("接收失败：%1").arg(serial.errorString()) << "\n";
	}
	QThread::sleep(1);  
    }
   
    serial.close();
    emit finished();
}
QString bmReader::getBmID(const QByteArray &bmDataPkg){
    return charToHexStr(bmDataPkg[3])
    	+ charToHexStr(bmDataPkg[4])
    	+ charToHexStr(bmDataPkg[5])
    	+ charToHexStr(bmDataPkg[6])
    	+ charToHexStr(bmDataPkg[7])
    	+ charToHexStr(bmDataPkg[8]);
}
QString bmReader::charToHexStr(char chr){
    return QString("%1").arg(chr, 2, 16, QLatin1Char('0')).toUpper().right(2);
}
