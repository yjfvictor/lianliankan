#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRegExp>
#include <QRegExpValidator>
#include <QMessageBox>
#include "myipdlg.h"

MyIpDlg::MyIpDlg(QWidget *parent) :
    QDialog(parent),
    ipAddrEdit(new QLineEdit(this)),
    okButton(new QPushButton(this)),
    cancelButton(new QPushButton(this)),
    ipAddrRegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)")
{
    setWindowTitle(tr("Please enter the IP address."));

    ipAddrEdit->setValidator(new QRegExpValidator(ipAddrRegExp, this));

    okButton->setText(tr("OK"));
    connect(okButton,SIGNAL(clicked()), this, SLOT(on_okButton_clicked()));

    cancelButton->setText(tr("Cancel"));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));


    QHBoxLayout * okCancelLayout = new QHBoxLayout;
    okCancelLayout->addWidget(okButton);
    okCancelLayout->addWidget(cancelButton);

    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(ipAddrEdit);
    mainLayout->addLayout(okCancelLayout);

    setLayout(mainLayout);

    setModal(true);
}

MyIpDlg::~MyIpDlg()
{
}

void MyIpDlg::on_okButton_clicked()
{
    if (validateIpAddress())
    {
        emit accept();
        return;
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("The IP address you input is incorrcted."), QMessageBox::Ok);
        ipAddrEdit->setFocus();
        return;
    }
}

QString MyIpDlg::getIpAddress()
{
    return ipAddrEdit->text();
}

bool MyIpDlg::validateIpAddress()
{
    return ipAddrRegExp.exactMatch(ipAddrEdit->text());
}

