#ifndef MYIPADDREDIT_H
#define MYIPADDREDIT_H

#include <QWidget>

class QLineEdit;
class QLabel;
class MyIpPartLineEdit;

class MyIpAddrEdit : public QWidget
{
    Q_OBJECT
public:
    explicit MyIpAddrEdit(QWidget *parent = 0);
    ~MyIpAddrEdit();
    void settext(const QString & text);
    QString text();
    void setStyleSheet(const QString & styleSheet);

signals:
    void textchanged(const QString& text);
    void textedited(const QString & text);

public slots:

private slots:
    void textchangedslot(const QString & text);
    void texteditedslot(const QString & text);

private:
    MyIpPartLineEdit * ipPart1;
    MyIpPartLineEdit * ipPart2;
    MyIpPartLineEdit * ipPart3;
    MyIpPartLineEdit * ipPart4;

    QLabel * labelDot1;
    QLabel * labelDot2;
    QLabel * labelDot3;

};

#endif // MYIPADDREDIT_H
