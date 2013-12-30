#include "mainwindow.h"
#include <QMessageBox>

int MainWindow::rows = 10;
int MainWindow::cols = 10;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      mainTableView(new MainTableView(this)),
      model(new MyItemModel(mainTableView,this)),
      statusBar(new QStatusBar(this)),
      mainToolBar(new QToolBar(this)),
      actionNew(new QAction(this)),
      actionRearrange(new QAction(this)),
      actionAbout(new QAction(this)),
      actionAboutQt(new QAction(this))
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

    QIcon iconAbout;
    iconAbout.addFile(QString(":/pic/about.png"), QSize(), QIcon::Normal, QIcon::Off);

    actionAbout->setText(tr("About"));
    actionAbout->setToolTip(tr("About"));
    actionAbout->setIcon(iconAbout);
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(about()));

    QIcon iconAboutQt;
    iconAboutQt.addFile(QString(":/pic/Qt.png"), QSize(), QIcon::Normal, QIcon::Off);

    actionAboutQt->setText(tr("About Qt"));
    actionAboutQt->setToolTip(tr("About Qt"));
    actionAboutQt->setIcon(iconAboutQt);
    connect(actionAboutQt, SIGNAL(triggered()), this, SLOT(aboutQt()));


    mainToolBar->addAction(actionNew);
    mainToolBar->addAction(actionRearrange);
    mainToolBar->addAction(actionAbout);
    mainToolBar->addAction(actionAboutQt);
    addToolBar(Qt::TopToolBarArea, mainToolBar);

    // 主窗格中的表格
    mainTableView->setModel(model);
    setCentralWidget(mainTableView);
    setStatusBar(statusBar);
    model->initialze();
    mainTableView->setWidth(25);
    connect(mainTableView, SIGNAL(clicked(QModelIndex)), model, SLOT(clickSlot(QModelIndex)) );

    // 连接模型的信号与本窗口的槽
    connect(model, SIGNAL(showMessage(QString,int)), this, SLOT(showMessage(QString,int)));
    connect(model, SIGNAL(clearMessage()), this, SLOT(clearMessage()));

    // 设置窗口大小
    resize(250, 350);
}

MainWindow::~MainWindow()
{
}

void MainWindow::showMessage(const QString &text, const int timeout)
{
    statusBar->showMessage(text, timeout);
}

void MainWindow::clearMessage()
{
    statusBar->clearMessage();
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About"), tr("Copyright © the fourth group of hnust C++ practice team\n"
                                             "Ye Jianfei, Wu Congyuan, Luo Yanmao, Li Chenlin, Lu Mujie"));
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}
