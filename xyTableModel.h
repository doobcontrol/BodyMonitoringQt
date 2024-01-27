#pragma once
#include <QAbstractTableModel>
#include "Equ.h"

class xyTableModel : public QAbstractTableModel
{
    Q_OBJECT
    QList<QMap<QString, QString>>* RowList = nullptr;
    QList<QMap<QString, QString>>* FieldsList = nullptr;
public:
    explicit xyTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    
    void addRows(QMap<QString, QString> rowMap);
    QString getPk(const int & row);
    QString getFieldCode(const int & column);
signals:
    void editCompleted(const int & row, const int & column, const QString &);
};
