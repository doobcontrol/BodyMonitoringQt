#include "xyTableModel.h"
#include "XyKModel.h"
#include <QColor>
#include <QDebug>

xyTableModel::xyTableModel(
    QList<QMap<QString, QString>>* RowList, 
    QList<QMap<QString, QString>>* FieldsList,
    QList<QString>* showFields, 
    QObject *parent)
    : QAbstractTableModel(parent)
{
    this->RowList = RowList;
    this->FieldsList = FieldsList;
    this->showFields = showFields;
    
    showFieldMaps = new QMap<QString, QMap<QString, QString>>;
    for(QMap<QString, QString> fMaps:(*FieldsList)){
         if(showFields->contains(fMaps[XyModel::XyBaseModel::FieldCode])){
             showFieldMaps->insert(fMaps[XyModel::XyBaseModel::FieldCode], fMaps);
         }
    }
}

int xyTableModel::rowCount(const QModelIndex & /*parent*/) const
{  
    return RowList->count();
}

int xyTableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return showFields->count();
}

QVariant xyTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole){            
        return RowList->value(index.row())
            [(*showFields)[index.column()]];
    }

    return QVariant();
}
QVariant xyTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        
        return (*showFieldMaps)[(*showFields)[section]][XyModel::XyBaseModel::FieldName];
    }
    return QVariant();
}
bool xyTableModel::insertRows(int row, int count, const QModelIndex & parent)
{            
    beginInsertRows(parent, row, row+(count-1));
    endInsertRows();
    return true;
}
void xyTableModel::addRows(QMap<QString, QString> rowMap){
    beginInsertRows(QModelIndex(), 0, 0);
    RowList->insert(0, rowMap);
    endInsertRows();
}
bool xyTableModel::removeRows(int row, int count, const QModelIndex & parent)
{   
    beginRemoveRows(parent, row, row+(count-1));
    
    endRemoveRows();
    return true;
}

bool xyTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
        if (!checkIndex(index))
            return false;
        
        if(value.toString()!=RowList->value(index.row())
            [(*showFields)[index.column()]]
            )
        {
            (*RowList)[index.row()] //
                [(*showFields)[index.column()]]=value.toString();
            emit editCompleted(RowList->value(index.row()), (*showFieldMaps)[(*showFields)[index.column()]]);
            
            emit dataChanged(index,index);
        }
        else{
            return false;
        }
        
        return true;
    }
    return false;
}
Qt::ItemFlags xyTableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}
