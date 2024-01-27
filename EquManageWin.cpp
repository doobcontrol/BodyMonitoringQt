
#include <QIcon>
#include <QToolBar>
#include <QVBoxLayout>
#include <QTableView>
#include "Equ.h"
#include <QDebug>
//#include <QFileSystemModel>
//#include <QDir>
#include "EquManageWin.h"

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
    toolbar->addAction(QIcon(":/Delete.png"), "删除");
    this->setWindowModality(Qt::ApplicationModal);   
    
    //QWidget *mainWidget = new QWidget(this);    
    //QVBoxLayout* vbox = new QVBoxLayout(this);
    //mainWidget->setLayout(vbox);
    //setCentralWidget(mainWidget);
    
    model = new xyTableModel(
        Equ::get()->selectAll(), 
        &Equ::get()->FieldsList, 
        this);
    
    tableView = new QTableView;         
    //vbox->addWidget(tableView, 0);
    setCentralWidget(tableView);
    
    tableView->setModel(model);    
    
    connect(model, &xyTableModel::editCompleted, this, &EquManageWin::UpdateEqu);
}
void EquManageWin::AddEqu(){
    QString newRecordID = Equ::get()->newRecord();
    model->addRows(*Equ::get()->selectByPk(newRecordID));
}
void EquManageWin::UpdateEqu(const QMap<QString, QString> recordMap, const QMap<QString, QString> fieldMap){
    Equ::get()->updateByRowColumn(recordMap,fieldMap);
}
