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
    // 生成各种颜色
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
        emit showMessage(tr("Error: cannot select empty grid."));
        tableView->clearSelection();
        return;
    }

    if ( last_selected_row == current_selected_row && last_selected_column == current_selected_column )
    {
        emit clearMessage();
        tableView->clearSelection();
        last_selected_row = last_selected_column = -1;
        current_selected_row = current_selected_column = -1;
    }
    else
    {
        if ( last_selected_row < 0 )
        {
            emit clearMessage();
            last_selected_row = current_selected_row;
            last_selected_column = current_selected_column;
        }
        else if (selectionCorrect())
        {
            emit showMessage(tr("Successfully clear a pair of grid."));
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
            emit showMessage(tr("Error: cannot connect"));
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
            //QPixmap pixmap(100,100);
            //pixmap.fill(QColor(grid[r][c]));
            QIcon buttonIcon;
            //buttonIcon.addPixmap(pixmap);
            buttonIcon.addFile(QString(":/photo/image/%1.png").arg(int(grid[r][c])));
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
    last_selected_row = last_selected_column = -1;
    refresh();
}

bool MyItemModel::selectionCorrect()
{
    Q_ASSERT( current_selected_row >= 0 );
    Q_ASSERT( current_selected_row < rowCount );
    Q_ASSERT( current_selected_column >= 0 );
    Q_ASSERT( current_selected_column < columnCount );

    Q_ASSERT( last_selected_row >= 0 );
    Q_ASSERT( last_selected_row < rowCount );
    Q_ASSERT( last_selected_column >= 0 );
    Q_ASSERT( last_selected_column < columnCount );

    Q_ASSERT( grid[current_selected_row][current_selected_column] != Qt::transparent );
    Q_ASSERT( grid[last_selected_row][last_selected_column] != Qt::transparent );

    if ( grid[last_selected_row][last_selected_column] != grid[current_selected_row][current_selected_column] )
        return false;

    for ( int r = 0; r < rowCount; ++ r)
    {
            for ( int c = 0; c < columnCount; ++ c)
                    visited[r][c] = false;
    }
    visited[current_selected_row][current_selected_column] = true;

    if ( current_selected_row > 0 )
    {
            if ( dfs( current_selected_row - 1, current_selected_column, Up ) )
                    return true;
    }
    else if ( current_selected_row == 0 )
    {
        for(int next_column = 0; next_column < columnCount; ++ next_column)
        {
            if ( next_column == current_selected_column )
                continue;
            if ( dfs(current_selected_row, next_column, Down, 2 ) )
                return true;
        }
    }

    if ( current_selected_column > 0 )
    {
            if ( dfs( current_selected_row, current_selected_column - 1, Left ) )
                    return true;
    }
    else if ( current_selected_column == 0 )
    {
        for ( int next_row = 0; next_row < rowCount; ++ next_row )
        {
            if ( next_row == current_selected_row )
                continue;
            if ( dfs( next_row, current_selected_column, Right, 2) )
                return true;
        }
    }

    if ( current_selected_row + 1 < rowCount )
    {
            if ( dfs( current_selected_row + 1, current_selected_column, Down ) )
                    return true;
    }
    else if ( current_selected_row + 1 == rowCount )
    {
        for ( int next_column = 0; next_column < columnCount; ++ next_column )
        {
            if ( next_column == current_selected_column )
                continue;
            if ( dfs( current_selected_row, next_column, Up, 2 ) )
                return true;
        }
    }

    if ( current_selected_column + 1 < columnCount )
    {
            if ( dfs( current_selected_row, current_selected_column + 1, Right ) )
                    return true;
    }
    else if ( current_selected_column + 1 == columnCount )
    {
        for ( int next_row = 0; next_row < rowCount; ++ next_row )
        {
            if ( next_row == current_selected_row )
                continue;
            if ( dfs( next_row, current_selected_column, Left, 2) )
                return true;
        }
    }


    return false;
}

bool MyItemModel::dfs(const int current_row, const int current_column, const MyItemModel::Direction direction, const int turning_count)
{
    Q_ASSERT( current_row >= 0 );
    Q_ASSERT( current_row < rowCount );
    Q_ASSERT( current_column >= 0 );
    Q_ASSERT( current_column < columnCount );

    if ( turning_count > 2 )
        return false;

    if ( visited[current_row][current_column] )
        return false;
    visited[current_row][current_column] = true;

    if ( current_row == last_selected_row && current_column == last_selected_column )
            return true;

    if ( grid[current_row][current_column] != Qt::transparent )
            return false;

    if ( current_row > 0 )
    {
            if ( dfs( current_row - 1, current_column, Up, ((direction==Up)?turning_count:(turning_count+1)) ) )
                    return true;
    }
    else if ( current_row == 0 )
    {
        for ( int next_column = 0; next_column < columnCount; ++ next_column )
        {
            if ( next_column == current_column )
                continue;
            if( dfs(0, next_column, Down, (turning_count + 2) ) )
                return true;
        }
    }

    if ( current_column > 0 )
    {
            if ( dfs( current_row, current_column - 1, Left, ((direction==Left)?turning_count:(turning_count+1)) ) )
                    return true;
    }
    else if ( current_column == 0 )
    {
        for ( int next_row = 0; next_row < rowCount; ++ next_row )
        {
            if ( next_row == current_row )
                continue;
            if ( dfs(next_row, 0, Right, (turning_count + 2) ) )
                return true;
        }
    }

    if ( current_row + 1 < rowCount )
    {
            if ( dfs( current_row + 1, current_column, Down, ((direction==Down)?turning_count:(turning_count+1)) ) )
                    return true;
    }
    else if ( current_row + 1 == rowCount )
    {
        for ( int next_column = 0; next_column < columnCount; ++ next_column )
        {
            if ( next_column == current_column )
                continue;
            if( dfs(current_row, next_column, Up, (turning_count + 2) ) )
                return true;
        }
    }

    if ( current_column + 1 < columnCount )
    {
            if ( dfs( current_row, current_column + 1, Right, ((direction==Right)?turning_count:(turning_count+1)) ) )
                    return true;
    }
    else if ( current_column + 1 == columnCount )
    {
        for ( int next_row = 0; next_row < rowCount; ++ next_row )
        {
            if ( next_row == current_row )
                continue;
            if ( dfs(next_row, current_column, Left, (turning_count + 2) ) )
                return true;
        }
    }

    visited[current_row][current_column] = false;
    return false;
}
