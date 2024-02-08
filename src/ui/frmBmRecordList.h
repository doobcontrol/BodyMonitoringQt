#pragma once
#include <QMainWindow>
#include <QCalendarWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QTableWidget>

class frmBmRecordList : public QMainWindow
{
    Q_OBJECT

public:
    frmBmRecordList(QWidget *parent = nullptr);

private slots:
    void getRecords();
    void selectRecord(int row, int column);
private:
    void createQueryGroupBox();    
    QGroupBox *queryGroupBox;
    QGridLayout *queryLayout;
    QCalendarWidget *calendar;
    
    QComboBox *roomComboBox();
    QComboBox *personComboBox();
    QComboBox *equComboBox();
    
    QTableWidget  *recordTable;

    QTableWidget  *itemTable;
    
    QList<QMap<QString, QString>>* bmRecrods;
    int selectedRecordIndex=-1;
};
