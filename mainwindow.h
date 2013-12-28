#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStatusBar>
#include <QToolBar>
#include <QAction>
#include "maintableview.h"
#include "myitemmodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    static int rows, cols;
    MainTableView * mainTableView;
    MyItemModel * model;
    QStatusBar *statusBar;
    QToolBar * mainToolBar;
    QAction * actionNew;
    QAction * actionRearrange;
};

#endif // MAINWINDOW_H
