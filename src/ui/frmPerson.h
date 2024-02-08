#pragma once
#include <QMainWindow>
#include "xyTableModel.h"
#include "xyTableView.h"

class frmPerson : public QMainWindow  {
public:
    frmPerson(QWidget *parent = nullptr);
private:
    xyTableView *tableView;
    xyTableModel *model;

public slots:
    void AddPerson();
    void EditPerson();
    void DeletePerson();
    void UpdatePerson(QMap<QString, QString> recordMap, QMap<QString, QString> fieldMap);
};
