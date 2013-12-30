#ifndef MYNETWORKCOMMUNICATION_H
#define MYNETWORKCOMMUNICATION_H

#include <QUdpSocket>

class MyNetworkCommunication : public QUdpSocket
{
    Q_OBJECT
public:
    explicit MyNetworkCommunication(QObject *parent = 0);
    ~MyNetworkCommunication();

signals:

public:
    void setMessageBoxParent(QWidget * msgBoxParent);
    void sendMessage(const QString & text);
    QString recvMessage();
    void setIpAddress(const QString & ipAddress);
    QString getIpAddress();
    void setPort(const quint16 port);
    quint16 getPort();

public slots:
    void tellingRunning();
    void tellingFinishing();
    void dealingMessage();
    void startGame();
    void tellingMessage();

private:
    QString messageToSend;
    QString messageRecving;
    QString ipAddress;
    quint16 port;
    volatile bool oppositeFinished;
    volatile bool ownFinished;
    QWidget * msgBoxParent;
};

#endif // MYNETWORKCOMMUNICATION_H
