#pragma once
#include <QMainWindow>
#include "xyTableModel.h"
#include "xyTableView.h"

class frmRoom : public QMainWindow  {
public:
    frmRoom(QWidget *parent = nullptr);
private:
    xyTableView *tableView;
    xyTableModel *model;

public slots:
    void AddRoom();
    void EditRoom();
    void DeleteRoom();
    void UpdateRoom(QMap<QString, QString> recordMap, QMap<QString, QString> fieldMap);
};
