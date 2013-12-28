#include "maintableview.h"
#include <QHeaderView>

MainTableView::MainTableView(QWidget *parent) :
    QTableView(parent)
{
    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::SingleSelection);
}

MainTableView::~MainTableView()
{
}
