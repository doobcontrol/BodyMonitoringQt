#pragma once
#include <QMainWindow>
#include "xyTableModel.h"
#include "xyTableView.h"

class EquManageWin : public QMainWindow  {
public:
    EquManageWin(QWidget *parent = nullptr);
private:
    xyTableView *tableView;
    xyTableModel *model;

public slots:
    void AddEqu();
    void EditEqu();
    void DeleteEqu();
    void UpdateEqu(QMap<QString, QString> recordMap, QMap<QString, QString> fieldMap);
};
