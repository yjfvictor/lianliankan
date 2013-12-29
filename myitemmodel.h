#ifndef MYITEMMODEL_H
#define MYITEMMODEL_H

#include <QStandardItemModel>
#include <QColor>
#include <QModelIndex>
#include <QTableView>
#include "data.h"

class MyItemModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit MyItemModel(QTableView * tableView = 0, QObject *parent = 0);
    ~MyItemModel();
    bool gameJustFinished();

public slots:
    void initialze();
    void clickSlot(const QModelIndex &index);
    void rearrange();

signals:

private:
    enum Direction { Left, Right, Up, Down };

    void refresh();
    bool selectionCorrect();
    bool dfs( const int current_row, const int current_column, const Direction direction, const int turning_count = 0 );

    static const int rowCount, columnCount;
    Qt::GlobalColor grid[MAX_ROWS][MAX_ROWS];
    bool visited[MAX_ROWS][MAX_ROWS];
    QTableView * tableView;

    int last_selected_row, last_selected_column;
    int current_selected_row, current_selected_column;
    bool playing;
};

#endif // MYITEMMODEL_H
