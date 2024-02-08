#pragma once
#include <QMainWindow>
#include <QLabel>
#include "xyTableModel.h"
#include "xyTableView.h"

class frmPerson : public QMainWindow  {
public:
    frmPerson(QWidget *parent = nullptr);
private:
    xyTableView *tableView;
    xyTableModel *model;
    QLabel *PhotoLabel;
    bool eventFilter(QObject *watched, QEvent *event);
    int selectedRecordIndex=-1;
public slots:
    void AddPerson();
    void EditPerson();
    void DeletePerson();
    void UpdatePerson(QMap<QString, QString> recordMap, QMap<QString, QString> fieldMap);
    void handlerRowChanged(const QModelIndex &current, const QModelIndex &previous);
};
