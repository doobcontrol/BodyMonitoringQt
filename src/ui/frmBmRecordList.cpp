#include "frmBmRecordList.h"
#include "bmRecord.h"
#include "bmRecordItem.h"
#include "MonitorPerson.h"
#include "MonitorRoom.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>

frmBmRecordList::frmBmRecordList(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("监测记录");
    setWindowIcon(QIcon(":/recordlist.png"));//只对windows有效，在linux下无效
    setFixedSize(1000, 600);
    setWindowFlags(Qt::Dialog);

    createQueryGroupBox();
    
    QHBoxLayout *hLayout=new QHBoxLayout;
    QVBoxLayout *vLayout=new QVBoxLayout; 
    
    vLayout->addWidget(queryGroupBox,0);    
    
    recordTable = new QTableWidget;    
    recordTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    recordTable->setSelectionMode(QAbstractItemView::SingleSelection);
    recordTable->setColumnCount(4);
    QStringList recordTableHeaderLabels = { "开始时间", "人员", "房间", "设备" };
    recordTable->setHorizontalHeaderLabels(recordTableHeaderLabels);
    recordTable->horizontalHeader()->setStretchLastSection(true);
    connect(recordTable, &QTableWidget::cellClicked, this, &frmBmRecordList::selectRecord);
    vLayout->addWidget(recordTable,1);   
     
    hLayout->addItem(vLayout); 
    
    itemTable = new QTableWidget;    
    itemTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    itemTable->setSelectionMode(QAbstractItemView::SingleSelection);
    itemTable->setColumnCount(3);
    QStringList itemTableHeaderLabels = { "时间", "心跳", "呼吸" };
    itemTable->setHorizontalHeaderLabels(itemTableHeaderLabels);
    itemTable->horizontalHeader()->setStretchLastSection(true);
    hLayout->addWidget(itemTable,1);   
     
    setLayout(hLayout);    
    
    getRecords();
}
void frmBmRecordList::createQueryGroupBox()
{
    queryGroupBox = new QGroupBox(tr("查找"));

    calendar = new QCalendarWidget;
    calendar->setMinimumDate(QDate(2020, 1, 1));
    calendar->setMaximumDate(QDate(2100, 1, 1));
    calendar->setGridVisible(true);

    connect(calendar, &QCalendarWidget::selectionChanged,
            this, &frmBmRecordList::getRecords);

    queryLayout = new QGridLayout;
    queryLayout->addWidget(calendar, 0, 0, Qt::AlignCenter);
    queryGroupBox->setLayout(queryLayout);    
}
void frmBmRecordList::getRecords()
{
    recordTable->clearContents();
    recordTable->setRowCount(0);
    itemTable->clearContents();
    itemTable->setRowCount(0);
    selectedRecordIndex=-1;
    
    bmRecrods = bmRecord::get()->selectByStartDate(calendar->selectedDate());
    for(QMap<QString, QString> onRecord:(* bmRecrods)){
        int rowCount=recordTable->rowCount();
        recordTable->insertRow(rowCount);
        QTableWidgetItem *newItem;
        
        newItem = new QTableWidgetItem(onRecord[bmRecord::fStartTimeID]);
        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
        recordTable->setItem(rowCount, 0, newItem);
        newItem = new QTableWidgetItem(onRecord[bmRecord::fPersonID+MonitorPerson::fPName]);
        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
        recordTable->setItem(rowCount, 1, newItem);
        newItem = new QTableWidgetItem(onRecord[bmRecord::fRoomID+MonitorRoom::fRoomCode]);
        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
        recordTable->setItem(rowCount, 2, newItem);
        newItem = new QTableWidgetItem(onRecord[bmRecord::fEquID]);
        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
        recordTable->setItem(rowCount, 3, newItem);
    }
}
void frmBmRecordList::selectRecord(int row, int column){
    if(selectedRecordIndex!=row){
        itemTable->clearContents();
        itemTable->setRowCount(0);
        QList<QMap<QString, QString>>* bmRecrodItems = bmRecordItem::get()->selectItemByRecord(
            (*bmRecrods)[row][XyKModel::fID]
            );
        for(QMap<QString, QString> onItem:(* bmRecrodItems)){
            int rowCount=itemTable->rowCount();
            itemTable->insertRow(rowCount);
            QTableWidgetItem *newItem;
        
            newItem = new QTableWidgetItem(onItem[bmRecordItem::fTimeID]);
            newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
            itemTable->setItem(rowCount, 0, newItem);
            newItem = new QTableWidgetItem(onItem[bmRecordItem::fBreathe]);
            newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
            itemTable->setItem(rowCount, 1, newItem);
            newItem = new QTableWidgetItem(onItem[bmRecordItem::fHeartRate]);
            newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
            itemTable->setItem(rowCount, 2, newItem);
        }
    
        selectedRecordIndex=row;
    }
}
