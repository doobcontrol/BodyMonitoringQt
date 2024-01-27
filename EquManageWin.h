#pragma once
#include <QMainWindow>
#include "xyTableModel.h"

class EquManageWin : public QMainWindow  {
public:
    EquManageWin(QWidget *parent = nullptr);
private:
    QTableView *tableView;
    xyTableModel *model;

public slots:
    void AddEqu();
    void UpdateEqu(const int & row, const int & column, const QString & value);
};
