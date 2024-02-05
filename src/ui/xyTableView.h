#pragma once
#include <QTableView>

class xyTableView : public QTableView {
public:
    xyTableView(QWidget *parent = nullptr);
    bool inEditing();
};
