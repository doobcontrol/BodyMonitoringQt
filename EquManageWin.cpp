
#include <QIcon>
#include <QToolBar>
#include <QVBoxLayout>
#include <QTableView>
#include "Equ.h"
#include <QDebug>
#include "EquManageWin.h"
#include <QMessageBox>

EquManageWin::EquManageWin(QWidget *parent)
: QMainWindow(parent){
    setWindowTitle("房间管理");
    setWindowIcon(QIcon(":/House.png"));//只对windows有效，在linux下无效
    resize(400, 300);
    
    QAction *tAction;
    
    QToolBar *toolbar = addToolBar("main toolbar");
    tAction = toolbar->addAction(QIcon(":/New.png"), "新增");
    connect(tAction, &QAction::triggered, this, &EquManageWin::AddEqu);
    toolbar->addAction(QIcon(":/Edit.png"), "修改");
    tAction = toolbar->addAction(QIcon(":/Delete.png"), "删除");
    connect(tAction, &QAction::triggered, this, &EquManageWin::DeleteEqu);
    this->setWindowModality(Qt::ApplicationModal); 
    
    QList<QString>* showFields=new QList<QString>;
    showFields->append(Equ::fEquRoom);
    showFields->append(Equ::fEquID);
    model = new xyTableModel(
        Equ::get()->selectAll(), 
        &Equ::get()->FieldsList, 
        showFields,
        this);
    
    tableView = new QTableView;    
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    setCentralWidget(tableView);
    
    tableView->setModel(model);    
    
    connect(model, &xyTableModel::editCompleted, this, &EquManageWin::UpdateEqu);
}
void EquManageWin::AddEqu(){
    QString newRecordID = Equ::get()->newRecord();
    model->addRows(*Equ::get()->selectByPk(newRecordID));
    tableView->selectRow(0);
    // Start editing the cell
    tableView->setCurrentIndex(model->index(0,0));
    tableView->edit(model->index(0,0));
}
void EquManageWin::DeleteEqu(){
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
        QString("确定要删除房间：%1 吗?").arg(rowMap[Equ::fEquRoom]), 
        QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No), 
        QMessageBox::NoButton);
    if(retButton!=QMessageBox::Yes){
        return;
    }
    
    Equ::get()->deleteByRow(rowMap);
    model->RowList->removeAt(rowInt);
    model->removeRows(rowInt, 1);
}
void EquManageWin::UpdateEqu(const QMap<QString, QString> recordMap, const QMap<QString, QString> fieldMap){
    Equ::get()->updateByRowColumn(recordMap,fieldMap);
}
