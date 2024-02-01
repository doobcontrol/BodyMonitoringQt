#pragma once
#include <QMainWindow>
#include <QLineEdit>

class MonitorInfoPanel : public QMainWindow  {
    Q_OBJECT
    QString bmID;
    QMap<QString, QString>* equMonitorObj=nullptr;
    QMap<QString, QString>* monitorRoom=nullptr;
    QMap<QString, QString>* monitorPerson=nullptr;
    void getMonitorInfo();
    QLineEdit roomIDEdit;
    QLineEdit personNameEdit;
public:
    MonitorInfoPanel(QString bmID, QWidget *parent = nullptr);
public slots:
    void saveSelection();
signals:
    void ok();
};
