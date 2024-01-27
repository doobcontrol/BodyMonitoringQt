#include <QApplication>
#include <QTextStream>
#include "bmMainWin.h"
#include "dbHelper.h"
#include "Equ.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    dbHelper::initXyBaseModelList.append(Equ::get());
    dbHelper::init();
    
    bmMainWin window;
    window.setWindowTitle("封闭式房间单人生命监测系统");
    window.show();
    
  return app.exec();
}
