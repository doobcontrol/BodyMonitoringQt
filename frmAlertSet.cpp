#include <QIcon>
#include <QToolBar>
#include <QDebug>
#include <QFormLayout>
#include <QLineEdit>
#include "frmAlertSet.h"
#include "ConfigPars.h"

frmAlertSet::frmAlertSet(QWidget *parent)
: QMainWindow(parent){
    setWindowTitle("报警参数");
    setWindowIcon(QIcon(":/alertset.png"));//只对windows有效，在linux下无效
    setFixedSize(300, 150);
    setWindowModality(Qt::ApplicationModal); 
    
    /*
    QAction *tAction;    
    QToolBar *toolbar = addToolBar("main toolbar");
    tAction = toolbar->addAction(QIcon(":/New.png"), "新增");
    connect(tAction, &QAction::triggered, this, &EquManageWin::AddEqu);
    tAction = toolbar->addAction(QIcon(":/Edit.png"), "修改");
    connect(tAction, &QAction::triggered, this, &EquManageWin::EditEqu);
    */    
    
    QLineEdit* tempEdit=nullptr;
    QFormLayout *formLayout = new QFormLayout();
    
    tempEdit=new QLineEdit(this);
    editMap[ConfigPars::HeartRateMax]=tempEdit;
    formLayout->addRow(tr("最大心跳:"), tempEdit);
    connect(tempEdit, &QLineEdit::textChanged, this, &frmAlertSet::saveValue);
    
    tempEdit=new QLineEdit(this);
    editMap[ConfigPars::HeartRateMin]=tempEdit;
    formLayout->addRow(tr("最小心跳:"), tempEdit);
    connect(tempEdit, &QLineEdit::textChanged, this, &frmAlertSet::saveValue);
    
    tempEdit=new QLineEdit(this);
    editMap[ConfigPars::BreatheMax]=tempEdit;
    formLayout->addRow(tr("最大呼吸:"), tempEdit);
    connect(tempEdit, &QLineEdit::textChanged, this, &frmAlertSet::saveValue);
    
    tempEdit=new QLineEdit(this);
    editMap[ConfigPars::BreatheMin]=tempEdit;
    formLayout->addRow(tr("最小呼吸:"), tempEdit);
    connect(tempEdit, &QLineEdit::textChanged, this, &frmAlertSet::saveValue);
    
    QWidget* mQWidget = new QWidget();
    mQWidget->setLayout(formLayout);
    setCentralWidget(mQWidget);
    
    QList<QMap<QString, QString>>* pList=ConfigPars::get()->selectAll();
    for(QMap<QString, QString> pMap:(*pList)){
        if(editMap.contains(pMap[XyKModel::fID])){
            editMap[pMap[XyKModel::fID]]->setText(pMap[ConfigPars::fParValue]);
        }
    }
}
void frmAlertSet::saveValue(QString newValue){
   // e.g. check with member variable
   QObject* obj = sender();
   for(QString key:editMap.keys()){
       if( obj == editMap[key] ){ 
           ConfigPars::get()->updateOneFieldByPk(key,ConfigPars::fParValue,newValue);
       }
   }
}
