#include "xyTableModel.h"
#include <QDebug>

xyTableModel::xyTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    RowList = Equ::get()->selectAll();
    FieldsList = &Equ::get()->FieldsList;
}

int xyTableModel::rowCount(const QModelIndex & /*parent*/) const
{  
    return RowList->count();
}

int xyTableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return FieldsList->count();
}

QVariant xyTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole){            
        return RowList->value(index.row())
            [FieldsList->value(index.column())[XyModel::XyBaseModel::FieldCode]];
    }

    return QVariant();
}
QVariant xyTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
    
        return FieldsList->value(section)[XyModel::XyBaseModel::FieldName];
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
       qDebug() << rowMap[Equ::fID];
    beginInsertRows(QModelIndex(), 0, 0);
    RowList->insert(0, rowMap); //rowCount()
    endInsertRows();
    //insertRows(0,1);
}
bool xyTableModel::removeRows(int row, int count, const QModelIndex & parent)
{   
    beginRemoveRows(parent, row, row+(count-1));
    
    endRemoveColumns();
    return true;
}

bool xyTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
        if (!checkIndex(index))
            return false;
        
        if(value.toString()!=RowList->value(index.row())
            [FieldsList->value(index.column())[XyModel::XyBaseModel::FieldCode]]
            ){
            emit editCompleted(index.row(), index.column(), value.toString());
            (*RowList)[index.row()] //
                [FieldsList->value(index.column())[XyModel::XyBaseModel::FieldCode]]=value.toString();
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
    
QString xyTableModel::getPk(const int & row)
{
    return RowList->value(row)[XyModel::XyKModel::fID];
}
QString xyTableModel::getFieldCode(const int & column)
{
    return FieldsList->value(column)[XyModel::XyBaseModel::FieldCode];
}
