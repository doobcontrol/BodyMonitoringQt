#pragma once
#include <QMainWindow>
#include <QLineEdit>
#include <QListWidget>
#include <QList>
#include <QMap>

class frmMonitorInfoSet : public QMainWindow  {
    Q_OBJECT
    QString bmID;
    QMap<QString, QString>* equMonitorObj=nullptr;
    QMap<QString, QString>* monitorRoom=nullptr;
    QMap<QString, QString>* monitorPerson=nullptr;
    void getMonitorInfo();
    QLineEdit roomIDEdit;
    QLineEdit personNameEdit;
    QListWidget *roomlistWidget;
    QListWidget *namelistWidget;
    QList<QMap<QString, QString>>* roomRowList;
    QList<QMap<QString, QString>>* personRowList;
public:
    frmMonitorInfoSet(QString bmID, QWidget *parent = nullptr);
public slots:
    void saveSelection();
    void setRoomFromList();
    void setPersonFromList();
signals:
    void ok();
};
