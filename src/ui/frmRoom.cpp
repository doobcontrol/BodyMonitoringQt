#include "MonitorRoom.h"
#include <QIcon>
#include <QToolBar>
#include <QVBoxLayout>
#include <QTableView>
#include <QDebug>
#include "frmRoom.h"
#include <QMessageBox>

frmRoom::frmRoom(QWidget *parent)
: QMainWindow(parent){
    setWindowTitle("房间管理");
    setWindowIcon(QIcon(":/House.png"));
    setFixedSize(400, 300);
    setWindowFlags(Qt::Dialog);
    this->setWindowModality(Qt::ApplicationModal); 
    
    QAction *tAction;
    
    QToolBar *toolbar = addToolBar("main toolbar");
    tAction = toolbar->addAction(QIcon(":/New.png"), "新增");
    connect(tAction, &QAction::triggered, this, &frmRoom::AddRoom);
    tAction = toolbar->addAction(QIcon(":/Edit.png"), "修改");
    connect(tAction, &QAction::triggered, this, &frmRoom::EditRoom);
    tAction = toolbar->addAction(QIcon(":/Delete.png"), "删除");
    connect(tAction, &QAction::triggered, this, &frmRoom::DeleteRoom);
    
    QList<QString>* showFields=new QList<QString>;
    showFields->append(MonitorRoom::fRoomCode);
    model = new xyTableModel(
        MonitorRoom::get()->selectAll(), 
        &MonitorRoom::get()->FieldsList, 
        showFields,
        this);
    
    tableView = new xyTableView;    
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    setCentralWidget(tableView);
    
    tableView->setModel(model);    
    
    connect(model, &xyTableModel::editCompleted, this, &frmRoom::UpdateRoom);
}
void frmRoom::AddRoom(){
    QString newRecordID = MonitorRoom::get()->newRecord();
    int row=model->RowList->count();
    model->addRows(*MonitorRoom::get()->selectByPk(newRecordID));
    tableView->selectRow(row);
    // Start editing the cell
    tableView->setCurrentIndex(model->index(row,0));
    tableView->edit(model->index(row,0));
}

void frmRoom::EditRoom(){
    if(tableView->inEditing()){
        return;
    }
    QList<QModelIndex> selectedRowsList = tableView->selectionModel()->selectedRows();
    if(selectedRowsList.count()==0){
        QMessageBox::critical(this, QString("出错"), QString("请选择要修改的项"));
        return;
    }
    int rowInt=selectedRowsList[0].row();
    tableView->setCurrentIndex(model->index(rowInt,0));
    tableView->edit(model->index(rowInt,0));
}
void frmRoom::DeleteRoom(){
    QList<QModelIndex> selectedRowsList = tableView->selectionModel()->selectedRows();
    if(selectedRowsList.count()==0){
        QMessageBox::critical(this, QString("出错"), QString("请选择要删除的项"));
        return;
    }
    int rowInt=selectedRowsList[0].row();
    QMap<QString, QString> rowMap = (*(model->RowList))[rowInt];
    
    //删除确认
    QMessageBox::StandardButton retButton = QMessageBox::question(this, 
        QString("删除确认"), 
        QString("确定要删除房间：%1 吗?").arg(rowMap[MonitorRoom::fRoomCode]), 
        QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No), 
        QMessageBox::NoButton);
    if(retButton!=QMessageBox::Yes){
        return;
    }
    
    MonitorRoom::get()->deleteByRow(rowMap);
    model->RowList->removeAt(rowInt);
    model->removeRows(rowInt, 1);
}
void frmRoom::UpdateRoom(const QMap<QString, QString> recordMap, const QMap<QString, QString> fieldMap){
    MonitorRoom::get()->updateByRowColumn(recordMap,fieldMap);
}
