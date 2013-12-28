#include "mainwindow.h"

int MainWindow::rows = 10;
int MainWindow::cols = 10;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      mainTableView(new MainTableView(this)),
      model(new MyItemModel(mainTableView,this)),
      statusBar(new QStatusBar(this)),
      mainToolBar(new QToolBar(this)),
      actionNew(new QAction(this)),
      actionRearrange(new QAction(this))
{
    // 窗口标题栏、图标设置
    setWindowTitle(tr("Lian Lian Kan"));
    QIcon windowIcon(QString(":/pic/victor.ico"));
    this->setWindowIcon(windowIcon);

    // 创建一个“新游戏”的图标
    QIcon iconNew;
    iconNew.addFile(QString(":/pic/new.png"), QSize(), QIcon::Normal, QIcon::Off);

    actionNew->setText(tr("New Game"));
    actionNew->setToolTip(tr("Start a new game"));
    actionNew->setIcon(iconNew);
    connect(actionNew, SIGNAL(triggered()), model, SLOT(initialze()));


    QIcon iconRearrange;
    iconRearrange.addFile(QString(":/pic/rearrange.png"), QSize(), QIcon::Normal, QIcon::Off);

    actionRearrange->setText(tr("Rearrange"));
    actionRearrange->setToolTip(tr("Rearrange the pictures"));
    actionRearrange->setIcon(iconRearrange);
    connect(actionRearrange, SIGNAL(triggered()), model, SLOT(rearrange()));


    mainToolBar->addAction(actionNew);
    mainToolBar->addAction(actionRearrange);
    addToolBar(Qt::TopToolBarArea, mainToolBar);

    // 主窗格中的表格
    mainTableView->setModel(model);
    setCentralWidget(mainTableView);
    setStatusBar(statusBar);
    model->initialze();
    connect(mainTableView, SIGNAL(clicked(QModelIndex)), model, SLOT(clickSlot(QModelIndex)) );

    // 设置窗口大小
    resize(700, 300);

}

MainWindow::~MainWindow()
{
}
