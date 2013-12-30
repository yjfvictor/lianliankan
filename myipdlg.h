#ifndef MYIPDLG_H
#define MYIPDLG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>

class MyIpDlg : public QDialog
{
    Q_OBJECT
public:
    explicit MyIpDlg(QWidget *parent = 0);
    ~MyIpDlg();
    QString getIpAddress();

signals:

public slots:

private:
    QLineEdit * ipAddrEdit;
    QPushButton * okButton;
    QPushButton * cancelButton;

    QRegExp ipAddrRegExp;

    bool validateIpAddress();

private slots:
    void on_okButton_clicked();
};

#endif // MYIPDLG_H
