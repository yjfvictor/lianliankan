#include "myitemmodel.h"
#include <QStandardItem>
#include <QIcon>
#include <QColor>
#include <QPixmap>
#include <cstdlib>
#include <ctime>
#include <QMessageBox>

const int MyItemModel::rowCount = MAX_ROWS;
const int MyItemModel::columnCount = MAX_ROWS;

MyItemModel::MyItemModel(QTableView * tableView, QObject *parent) :
    QStandardItemModel(parent),
    last_selected_row(-1),
    last_selected_column(-1),
    playing(false)
{
    srand(time(NULL));

    setRowCount(rowCount);
    setColumnCount(columnCount);

    this->tableView = tableView;
}

MyItemModel::~MyItemModel()
{
}

void MyItemModel::initialze()
{

    // 随机生成各种颜色
    for ( int r = 0; r < rowCount; ++ r)
    {
        for ( int c = 0; c < columnCount; ++ c)
            grid[r][c] = Qt::GlobalColor( ( (r*columnCount+c) % 8 ) + 6 );
    }

    rearrange();
    playing = true;
}

void MyItemModel::clickSlot(const QModelIndex &index)
{
    current_selected_row = index.row();
    current_selected_column = index.column();

    if ( grid[current_selected_row][current_selected_column] == Qt::transparent )
    {
        tableView->clearSelection();
        return;
    }

    if ( last_selected_row == current_selected_row && last_selected_column == current_selected_column )
    {
        tableView->clearSelection();
        last_selected_row = last_selected_column = -1;
        current_selected_row = current_selected_column = -1;
    }
    else
    {
        if (selectionCorrect())
        {
            grid[last_selected_row][last_selected_column] = grid[current_selected_row][current_selected_column] = Qt::transparent;
            last_selected_row = last_selected_column = -1;
            current_selected_row = current_selected_column = -1;
            refresh();
            if ( gameJustFinished() )
            {
                last_selected_row = last_selected_column = -1;
                current_selected_row = current_selected_column = -1;
                QMessageBox::warning(tableView, tr("Lian Lian Kan"), tr("Game over"), QMessageBox::Ok);
            }
        }
        else
        {
            last_selected_row = current_selected_row;
            last_selected_column = current_selected_column;
        }
    }
}

void MyItemModel::refresh()
{
    tableView->clearSelection();
    // 把数组中的颜色数据显示到表格中
    for ( int r = 0; r < rowCount; ++ r)
    {
        for ( int c = 0; c < columnCount; ++ c )
        {
            QPixmap pixmap(100,100);
            pixmap.fill(QColor(grid[r][c]));
            QIcon buttonIcon;
            buttonIcon.addPixmap(pixmap);
            setItem(r,c, new QStandardItem(buttonIcon,QString("")));
        }
    }
}

bool MyItemModel::gameJustFinished()
{
    if ( playing )
    {
        for ( int r = 0; r < rowCount; ++ r )
        {
            for ( int c = 0; c < columnCount; ++ c )
            {
                if ( grid[r][c] != Qt::transparent )
                    return false;
            }
        }
        playing = false;
        return true;
    }
    else
        return false;
}

void MyItemModel::rearrange()
{
    // 随机交换两个格子的颜色，即打散颜色
    for ( int r = 0; r < rowCount; ++ r)
    {
        for ( int c = 0; c < columnCount; ++ c)
        {
            int randRow = rand() % rowCount;
            int randColumn = rand() % columnCount;
            Qt::GlobalColor temp = grid[r][c];
            grid[r][c] = grid[randRow][randColumn];
            grid[randRow][randColumn] = temp;
        }
    }
    refresh();
}

bool MyItemModel::selectionCorrect()
{
    return grid[last_selected_row][last_selected_column] == grid[current_selected_row][current_selected_column];
}
