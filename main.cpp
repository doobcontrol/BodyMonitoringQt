#include <QApplication>
#include <QTextStream>
#include "bmMainWin.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    bmMainWin window;

    window.setWindowTitle("封闭式房间单人生命监测系统");
    window.show();
    
  return app.exec();
}
