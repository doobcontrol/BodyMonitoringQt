######################################################################
# Automatically generated by qmake (3.1) Sun Feb 4 05:14:17 2024
######################################################################

TEMPLATE = app
TARGET = BodyMonitoringQt
INCLUDEPATH += .

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += bmReader.h \
           ui/bmDataShow.h \
           ui/bmMainWin.h \
           ui/EquManageWin.h \
           ui/frmAlertSet.h \
           ui/MonitorInfoPanel.h \
           ui/xyTableModel.h \
           ui/xyTableView.h \
           xyModel/bmRecord.h \
           xyModel/bmRecordItem.h \
           xyModel/ConfigPars.h \
           xyModel/dbHelper.h \
           xyModel/Equ.h \
           xyModel/EquMonitorObj.h \
           xyModel/MonitorPerson.h \
           xyModel/MonitorRoom.h \
           xyModel/XyBaseModel.h \
           xyModel/XyKModel.h
SOURCES += bmReader.cpp \
           main.cpp \
           ui/bmDataShow.cpp \
           ui/bmMainWin.cpp \
           ui/EquManageWin.cpp \
           ui/frmAlertSet.cpp \
           ui/MonitorInfoPanel.cpp \
           ui/xyTableModel.cpp \
           ui/xyTableView.cpp \
           xyModel/bmRecord.cpp \
           xyModel/bmRecordItem.cpp \
           xyModel/ConfigPars.cpp \
           xyModel/dbHelper.cpp \
           xyModel/Equ.cpp \
           xyModel/EquMonitorObj.cpp \
           xyModel/MonitorPerson.cpp \
           xyModel/MonitorRoom.cpp \
           xyModel/XyBaseModel.cpp \
           xyModel/XyKModel.cpp
RESOURCES += resource.qrc
DESTDIR = bin
MOC_DIR = tmp
OBJECTS_DIR  = tmp
RCC_DIR = tmp

QT += widgets 
QT += serialport 
QT += charts
QT += sql
QT += multimedia
