#include <QApplication>
#include <QTextStream>
#include "bmMainWin.h"
#include "bmReader.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    bmMainWin window;

    window.setWindowTitle("封闭式房间单人生命监测系统");
    window.show();
  
    bmReader bm;

    QObject::connect( &bm, &bmReader::serialPortErro, &window, &bmMainWin::logErro );
    QObject::connect( &bm, &bmReader::bmDataGot, &window, &bmMainWin::logbmData );
    
    bm.start();
    
  return app.exec();
}
