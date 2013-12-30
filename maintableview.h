#ifndef MAINTABLEVIEW_H
#define MAINTABLEVIEW_H

#include <QTableView>

class MainTableView : public QTableView
{
    Q_OBJECT
public:
    explicit MainTableView(QWidget *parent = 0);
    ~MainTableView();

signals:

public slots:

public:
    void setWidth(int width);

};

#endif // MAINTABLEVIEW_H
