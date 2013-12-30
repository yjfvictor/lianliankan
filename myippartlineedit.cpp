#include "myippartlineedit.h"
#include <QIntValidator>
#include <QKeyEvent>

MyIpPartLineEdit::MyIpPartLineEdit(QWidget *parent) :
    QLineEdit(parent), nextTab(NULL)
{
    setMaxLength(3);
    setFrame(false);
    setAlignment(Qt::AlignCenter);
    QValidator *validator = new QIntValidator(0, 255, this);
    setValidator(validator);
    connect(this, SIGNAL(textEdited(const QString &)), this, SLOT(textEditedSlot(const QString &)));
}

MyIpPartLineEdit::~MyIpPartLineEdit()
{
}

void MyIpPartLineEdit::setNexttabEdit(QLineEdit *nextTab)
{
    this->nextTab = nextTab;
}

void MyIpPartLineEdit::textEditedSlot(const QString &text)
{
    QIntValidator v(0, 255, this);
    QString ipaddr = text;
    int pos = 0;
    QValidator::State state = v.validate(ipaddr, pos);
    if (state == QValidator::Acceptable)
    {
        if (ipaddr.size() > 1)
        {
            if (ipaddr.size() == 2)
            {
                int ipnum = ipaddr.toInt();

                if (ipnum > 25)
                {
                    if (nextTab)
                    {
                        nextTab->setFocus();
                        nextTab->selectAll();
                    }
                }
            }
            else
            {
                if (nextTab)
                {
                    nextTab->setFocus();
                    nextTab->selectAll();
                }
            }
        }
    }
}

void MyIpPartLineEdit::focusInEvent(QFocusEvent *e)
{
    selectAll();
    QLineEdit::focusInEvent(e);
}

void MyIpPartLineEdit::keyPressEvent(QKeyEvent *event)
{
    if ( event->key() == Qt::Key_Period )
    {
        if ( nextTab )
        {
            nextTab->setFocus();
            nextTab->selectAll();
        }
    }
    QLineEdit::keyPressEvent(event);
}
