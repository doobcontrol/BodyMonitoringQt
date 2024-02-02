#pragma once
#include <QAbstractTableModel>

class xyTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit xyTableModel(
        QList<QMap<QString, QString>>* RowList, 
        QList<QMap<QString, QString>>* FieldsList, 
        QList<QString>* showFields, 
        QObject *parent = nullptr);
    QList<QMap<QString, QString>>* RowList = nullptr;
    QList<QMap<QString, QString>>* FieldsList = nullptr;
    
    QList<QString>* showFields = nullptr;    
    QMap<QString, QMap<QString, QString>>* showFieldMaps = nullptr;

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
    void editCompleted(const QMap<QString, QString> recordMap, const QMap<QString, QString> fieldMap);
};
