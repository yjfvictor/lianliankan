#include "myipaddredit.h"
#include <QRegExpValidator>
#include <QLabel>
#include "myippartlineedit.h"

MyIpAddrEdit::MyIpAddrEdit(QWidget *parent) :
    QWidget(parent),
    ipPart1(new MyIpPartLineEdit(this)),
    ipPart2(new MyIpPartLineEdit(this)),
    ipPart3(new MyIpPartLineEdit(this)),
    ipPart4(new MyIpPartLineEdit(this)),
    labelDot1(new QLabel(this)),
    labelDot2(new QLabel(this)),
    labelDot3(new QLabel(this))
{
    ipPart1->setGeometry(QRect(0, 0, 30, 20));
    ipPart2->setGeometry(QRect(30, 0, 30, 20));
    ipPart3->setGeometry(QRect(60, 0, 30, 20));
    ipPart4->setGeometry(QRect(90, 0, 30, 20));

    labelDot1->setText(" .");
    labelDot1->setGeometry(QRect(27, 1, 6, 18));
    labelDot1->setAlignment(Qt::AlignCenter);

    labelDot2->setText(" .");
    labelDot2->setGeometry(QRect(57, 1, 6, 18));
    labelDot2->setAlignment(Qt::AlignCenter);

    labelDot3->setText(" .");
    labelDot3->setGeometry(QRect(87, 1, 6, 18));
    labelDot3->setAlignment(Qt::AlignCenter);

    setTabOrder(ipPart1, ipPart2);
    setTabOrder(ipPart2, ipPart3);
    setTabOrder(ipPart3, ipPart4);

    ipPart1->setNexttabEdit(ipPart2);
    ipPart2->setNexttabEdit(ipPart3);
    ipPart3->setNexttabEdit(ipPart4);

    connect(ipPart1, SIGNAL(textChanged(const QString&)), this, SLOT(textchangedslot(const QString&)));
    connect(ipPart2, SIGNAL(textChanged(const QString&)), this, SLOT(textchangedslot(const QString&)));
    connect(ipPart3, SIGNAL(textChanged(const QString&)), this, SLOT(textchangedslot(const QString&)));
    connect(ipPart4, SIGNAL(textChanged(const QString&)), this, SLOT(textchangedslot(const QString&)));

    connect(ipPart1, SIGNAL(textEdited(const QString&)), this, SLOT(texteditedslot(const QString&)));
    connect(ipPart2, SIGNAL(textEdited(const QString&)), this, SLOT(texteditedslot(const QString&)));
    connect(ipPart3, SIGNAL(textEdited(const QString&)), this, SLOT(texteditedslot(const QString&)));
    connect(ipPart4, SIGNAL(textEdited(const QString&)), this, SLOT(texteditedslot(const QString&)));
}

MyIpAddrEdit::~MyIpAddrEdit()
{
}

void MyIpAddrEdit::textchangedslot(const QString &text)
{
    QString ippart1, ippart2, ippart3, ippart4;

    ippart1 = ipPart1->text();
    ippart2 = ipPart2->text();
    ippart3 = ipPart3->text();
    ippart4 = ipPart4->text();

    QString ipaddr = QString("%1.%2.%3.%4").arg(ippart1).arg(ippart2).arg(ippart3).arg(ippart4);

    emit textchanged(ipaddr);
}

void MyIpAddrEdit::texteditedslot(const QString &text)
{
    QString ippart1, ippart2, ippart3, ippart4;
    ippart1 = ipPart1->text();
    ippart2 = ipPart2->text();
    ippart3 = ipPart3->text();
    ippart4 = ipPart4->text();

    QString ipaddr = QString("%1.%2.%3.%4")
        .arg(ippart1)
        .arg(ippart2)
        .arg(ippart3)
        .arg(ippart4);

    emit textedited(ipaddr);
}

void MyIpAddrEdit::settext(const QString &text)
{
    QString ippart1, ippart2, ippart3, ippart4;
    QString qstring_validate = text;

    // IP地址验证
    QRegExp regexp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    QRegExpValidator regexp_validator(regexp, this);
    int nPos = 0;
    QValidator::State state = regexp_validator.validate(qstring_validate, nPos);
    // IP合法
    if (state == QValidator::Acceptable)
    {
        QStringList ippartlist = text.split(".");

        int strcount = ippartlist.size();
        int index = 0;
        if (index < strcount)
        {
            ippart1 = ippartlist.at(index);
        }
        if (++index < strcount)
        {
            ippart2 = ippartlist.at(index);
        }
        if (++index < strcount)
        {
            ippart3 = ippartlist.at(index);
        }
        if (++index < strcount)
        {
            ippart4 = ippartlist.at(index);
        }
    }

    ipPart1->setText(ippart1);
    ipPart2->setText(ippart2);
    ipPart3->setText(ippart3);
    ipPart4->setText(ippart4);
}

QString MyIpAddrEdit::text()
{
    QString ippart1, ippart2, ippart3, ippart4;
    ippart1 = ipPart1->text();
    ippart2 = ipPart2->text();
    ippart3 = ipPart3->text();
    ippart4 = ipPart4->text();

    return QString("%1.%2.%3.%4").arg(ippart1).arg(ippart2).arg(ippart3).arg(ippart4);
}

void MyIpAddrEdit::setStyleSheet(const QString &styleSheet)
{
    ipPart1->setStyleSheet(styleSheet);
    ipPart2->setStyleSheet(styleSheet);
    ipPart3->setStyleSheet(styleSheet);
    ipPart4->setStyleSheet(styleSheet);
}
