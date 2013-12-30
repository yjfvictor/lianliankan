#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStatusBar>
#include <QToolBar>
#include <QAction>
#include "maintableview.h"
#include "myitemmodel.h"
#include "mynetworkcommunication.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void showMessage(const QString & text, const int timeout);
    void clearMessage();
    void network();
    void about();
    void aboutQt();

private:
    static int rows, cols;
    MainTableView * mainTableView;
    MyItemModel * model;
    QStatusBar *statusBar;
    QToolBar * mainToolBar;
    QAction * actionNew;
    QAction * actionRearrange;
    QAction * actionNetwork;
    QAction * actionAbout;
    QAction * actionAboutQt;

    MyNetworkCommunication * networkCommunication;
    bool playOnline;
};

#endif // MAINWINDOW_H
