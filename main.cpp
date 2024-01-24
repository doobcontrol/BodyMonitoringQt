#include <QApplication>
#include <QTextStream>
#include "bmMainWin.h"
#include "dbHelper.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    dbHelper::init();
    
    bmMainWin window;
    window.setWindowTitle("封闭式房间单人生命监测系统");
    window.show();
    
  return app.exec();
}
