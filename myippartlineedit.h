#ifndef MYIPPARTLINEEDIT_H
#define MYIPPARTLINEEDIT_H

#include <QLineEdit>

class MyIpPartLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyIpPartLineEdit(QWidget *parent = 0);
    ~MyIpPartLineEdit();

    void setNexttabEdit(QLineEdit *nexttab);

protected:
    virtual void focusInEvent(QFocusEvent *e);
    virtual void keyPressEvent(QKeyEvent *event);

signals:

public slots:

private slots:
    void textEditedSlot(const QString& text);

private:
    QLineEdit * nextTab;

};

#endif // MYIPPARTLINEEDIT_H
