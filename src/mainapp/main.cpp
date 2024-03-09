#include <QApplication>
#include <QTextStream>
#include <QDir>
#include "bmMainWin.h"
#include "dbHelper.h"
#include "ConfigPars.h"
#include "MonitorPerson.h"
#include "MonitorRoom.h"
#include "EquMonitorObj.h"
#include "bmRecord.h"
#include "bmRecordItem.h"
#include <QTranslator>
#include <QDebug>
#include <QFile>
#include <QtGlobal>

void myMessageHandler(QtMsgType type, const QMessageLogContext &, const QString & str);

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    QString workDir = QDir::homePath().append("/BodyMonitoringQt");
    (new QDir(workDir))->mkpath(".");
    bmMainWin::workDir=workDir;
    bmMainWin::dataDir=workDir;
    bmMainWin::dataDir.append(QString("/data"));
    (new QDir(bmMainWin::dataDir))->mkpath(".");
    
    QString outFileStr(bmMainWin::workDir);
    outFileStr.append(QString("/log"));    
    QFile outFile(outFileStr);
    if(outFile.exists()){
        outFile.remove();
    }
    
    qInstallMessageHandler(myMessageHandler);	
    qDebug() << QString("程序启动");
    
    //加载Qt标准对话框的中文翻译文件 (摘自网络)
    //可从安装目录拷贝：/usr/share/qt5/translations/qtbase_zh_CN.qm
    QTranslator tran;
    bool ok = tran.load(":/qtbase_zh_CN.qm");
    if(ok){
    	app.installTranslator(&tran);
    }
    else{    
        qDebug() << QString("加载汉化文件失败");
    }
    
    dbHelper::initXyBaseModelList.append(ConfigPars::get());
    dbHelper::initXyBaseModelList.append(MonitorPerson::get());
    dbHelper::initXyBaseModelList.append(MonitorRoom::get());
    dbHelper::initXyBaseModelList.append(EquMonitorObj::get());
    dbHelper::initXyBaseModelList.append(bmRecord::get());
    dbHelper::initXyBaseModelList.append(bmRecordItem::get());
    QString dbFile=workDir;
    dbFile.append(QString("/bm.db"));
    dbHelper::init(dbFile);
    
    bmMainWin window;
    window.setWindowTitle("封闭式房间单人生命监测系统");
    window.show();
    
    int retInt=app.exec();	
    qDebug() << QString("程序停止");
    
    return retInt;
}

void myMessageHandler(QtMsgType type, const QMessageLogContext &, const QString & msg)
{
    //const char * msg = str;//.toStdString().c_str();
    QString txt;
    QString TimeStr=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    switch (type) {
    case QtDebugMsg:
        txt = QString("%2: Debug: %1").arg(msg).arg(TimeStr);
        break;
    case QtWarningMsg:
        txt = QString("%2: Warning: %1").arg(msg).arg(TimeStr);
        break;
    case QtCriticalMsg:
        txt = QString("%2: Critical: %1").arg(msg).arg(TimeStr);
        break;
    case QtFatalMsg:
        txt = QString("%2: Fatal: %1").arg(msg).arg(TimeStr);
        abort();
    }
    QString outFileStr(bmMainWin::workDir);
    outFileStr.append(QString("/log"));    
    QFile outFile(outFileStr);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    //ts.setEncoding(QStringConverter::Utf8);
    ts << txt << Qt::endl;
    outFile.close();
}
