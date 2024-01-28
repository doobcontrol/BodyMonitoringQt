
#include "xyTableView.h"


xyTableView::xyTableView(QWidget *parent)
: QTableView(parent){
}
bool xyTableView::inEditing()
{
    return state() == QAbstractItemView::EditingState;
}
