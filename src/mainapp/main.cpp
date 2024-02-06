#include <QApplication>
#include <QTextStream>
#include <QDir>
#include "bmMainWin.h"
#include "dbHelper.h"
#include "Equ.h"
#include "ConfigPars.h"
#include "MonitorPerson.h"
#include "MonitorRoom.h"
#include "EquMonitorObj.h"
#include "bmRecord.h"
#include "bmRecordItem.h"
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
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
    
    QString workDir = QDir::homePath().append("/BodyMonitoringQt");
    (new QDir(workDir))->mkpath(".");
    bmMainWin::workDir=workDir;
    bmMainWin::dataDir=workDir;
    bmMainWin::dataDir.append(QString("/data"));
    (new QDir(bmMainWin::dataDir))->mkpath(".");
    
    dbHelper::initXyBaseModelList.append(Equ::get());
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
    
  return app.exec();
}
