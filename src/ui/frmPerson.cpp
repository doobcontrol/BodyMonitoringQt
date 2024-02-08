#include "frmPerson.h"
#include "MonitorPerson.h"
#include <QIcon>
#include <QToolBar>
#include <QVBoxLayout>
#include <QTableView>
#include <QDebug>
#include <QMessageBox>

frmPerson::frmPerson(QWidget *parent)
: QMainWindow(parent){
    setWindowTitle("人员管理");
    setWindowIcon(QIcon(":/monitorobj.png"));
    setFixedSize(400, 300);
    setWindowFlags(Qt::Dialog);
    this->setWindowModality(Qt::ApplicationModal); 
    
    QAction *tAction;
    
    QToolBar *toolbar = addToolBar("main toolbar");
    tAction = toolbar->addAction(QIcon(":/New.png"), "新增");
    connect(tAction, &QAction::triggered, this, &frmPerson::AddPerson);
    tAction = toolbar->addAction(QIcon(":/Edit.png"), "修改");
    connect(tAction, &QAction::triggered, this, &frmPerson::EditPerson);
    tAction = toolbar->addAction(QIcon(":/Delete.png"), "删除");
    connect(tAction, &QAction::triggered, this, &frmPerson::DeletePerson);
    
    QList<QString>* showFields=new QList<QString>;
    showFields->append(MonitorPerson::fPName);
    model = new xyTableModel(
        MonitorPerson::get()->selectAll(), 
        &MonitorPerson::get()->FieldsList, 
        showFields,
        this);
    
    tableView = new xyTableView;    
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    setCentralWidget(tableView);
    
    tableView->setModel(model);    
    
    connect(model, &xyTableModel::editCompleted, this, &frmPerson::UpdatePerson);
}
void frmPerson::AddPerson(){
    QString newRecordID = MonitorPerson::get()->newRecord();
    model->addRows(*MonitorPerson::get()->selectByPk(newRecordID));
    tableView->selectRow(0);
    // Start editing the cell
    tableView->setCurrentIndex(model->index(0,0));
    tableView->edit(model->index(0,0));
}

void frmPerson::EditPerson(){
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
void frmPerson::DeletePerson(){
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
        QString("确定要删除人员：%1 吗?").arg(rowMap[MonitorPerson::fPName]), 
        QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No), 
        QMessageBox::NoButton);
    if(retButton!=QMessageBox::Yes){
        return;
    }
    
    MonitorPerson::get()->deleteByRow(rowMap);
    model->RowList->removeAt(rowInt);
    model->removeRows(rowInt, 1);
}
void frmPerson::UpdatePerson(const QMap<QString, QString> recordMap, const QMap<QString, QString> fieldMap){
    MonitorPerson::get()->updateByRowColumn(recordMap,fieldMap);
}
