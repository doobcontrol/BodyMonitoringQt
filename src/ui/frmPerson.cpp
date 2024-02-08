#include "frmPerson.h"
#include "MonitorPerson.h"
#include "bmMainWin.h"
#include <QIcon>
#include <QToolBar>
#include <QVBoxLayout>
#include <QTableView>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>

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
    tableView->setModel(model);
    connect(tableView->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &frmPerson::handlerRowChanged);
    
    QHBoxLayout *hLayout=new QHBoxLayout;    
    hLayout->addWidget(tableView,1);   
    
    PhotoLabel=new QLabel();
    PhotoLabel->resize(150,200);
    PhotoLabel->setToolTip("双击设置人员照片");
    PhotoLabel->installEventFilter(this);//加事件过滤器以接收双击事件     
    PhotoLabel->setVisible(false);
    hLayout->addWidget(PhotoLabel,0);   
     
    setCentralWidget(new QWidget);
    centralWidget()->setLayout(hLayout);
        
    
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
    
    QString persionID=rowMap[XyKModel::fID];
    MonitorPerson::get()->deletePerson(persionID);
    
    //删除照片。原设计在MonitorPerson中删除照片。但目前简化编程，只有以fID为名的文件名，无路径，因此暂在此处删除  
    QString targetFile(bmMainWin::dataDir);
    targetFile.append(QString("/%1").arg(persionID));
    if(QFile::exists(targetFile)){
        QFile::remove(targetFile);
    }
    
    model->RowList->removeAt(rowInt);
    model->removeRows(rowInt, 1);
}
void frmPerson::UpdatePerson(const QMap<QString, QString> recordMap, const QMap<QString, QString> fieldMap){
    MonitorPerson::get()->updateByRowColumn(recordMap,fieldMap);
}
bool frmPerson::eventFilter(QObject *watched, QEvent *event){
    if(qobject_cast<QLabel*>(watched) == PhotoLabel && event->type() == QEvent::MouseButtonDblClick)
    {
        QList<QModelIndex> selectedRowsList = tableView->selectionModel()->selectedRows();
        if(selectedRowsList.count()==0){
            QMessageBox::critical(this, QString("出错"), QString("请选择人员"));
            return true;
        }
        int rowInt=selectedRowsList[0].row();
        QMap<QString, QString> rowMap = (*(model->RowList))[rowInt];
        
        QString fileName = QFileDialog::getOpenFileName(this,
            tr("选择照片"), "/home", tr("照片文件 (*.png *.jpg *.bmp)"));    
        if(fileName.isEmpty()){
            return true;
        }
        QString targetFile(bmMainWin::dataDir);
        targetFile.append(QString("/%1").arg(rowMap[XyKModel::fID]));
        if(QFile::exists(targetFile)){
            QFile::remove(targetFile);
        }
        QFile::copy(fileName,targetFile);
        
        QPixmap pm(targetFile);
        // get label dimensions
        int w = 150;//PhotoLabel->width();
        int h = 200;//PhotoLabel->height();
        // set a scaled pixmap to a w x h window keeping its aspect ratio 
        PhotoLabel->setPixmap(pm.scaled(w,h,Qt::KeepAspectRatio));
                    
        return true;
    }
    return false;
}
void frmPerson::handlerRowChanged(const QModelIndex &current, const QModelIndex &previous){
    int row=current.row();
    if(selectedRecordIndex!=row){        
        QMap<QString, QString> rowMap = (*(model->RowList))[row];
        QString targetFile(bmMainWin::dataDir);
        targetFile.append(QString("/%1").arg(rowMap[XyKModel::fID]));
        if(!QFile::exists(targetFile)){
            targetFile=":/photoicon.png";
        }
            
        QPixmap pm(targetFile);
        // get label dimensions
        int w = 150;//PhotoLabel->width();
        int h = 200;//PhotoLabel->height();
        // set a scaled pixmap to a w x h window keeping its aspect ratio 
        PhotoLabel->setPixmap(pm.scaled(w,h,Qt::KeepAspectRatio));
    
        selectedRecordIndex=row;          
        PhotoLabel->setVisible(false);
        PhotoLabel->show();
    }
}
