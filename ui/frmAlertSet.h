#pragma once
#include <QMainWindow>

class frmAlertSet : public QMainWindow  {
public:
    frmAlertSet(QWidget *parent = nullptr);
private:
    QMap<QString, QLineEdit*> editMap;
public slots:
    void saveValue(QString newValue);
};
