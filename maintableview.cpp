#include "maintableview.h"
#include "data.h"
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

void MainTableView::setWidth(int width)
{
    for( int i = 0; i < MAX_ROWS; ++ i )
        setColumnWidth(i, width);
}
