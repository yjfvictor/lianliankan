#include <QHostAddress>
#include <QMessageBox>
#include <QThread>
#include "mynetworkcommunication.h"
#include "data.h"

MyNetworkCommunication::MyNetworkCommunication(QObject *parent) :
    QUdpSocket(parent), ipAddress("255.255.255.255"), port(0),
    oppositeFinished(false), ownFinished(false), msgBoxParent(NULL)
{
}

MyNetworkCommunication::~MyNetworkCommunication()
{
}

void MyNetworkCommunication::setIpAddress(const QString &ipAddress)
{
    this->ipAddress = ipAddress;
}

QString MyNetworkCommunication::getIpAddress()
{
    return ipAddress;
}

void MyNetworkCommunication::setPort(const quint16 port)
{
    this->port = port;
}

quint16 MyNetworkCommunication::getPort()
{
    return port;
}

void MyNetworkCommunication::setMessageBoxParent(QWidget *msgBoxParent)
{
    this->msgBoxParent = msgBoxParent;
}

void MyNetworkCommunication::tellingRunning()
{
    if ( !oppositeFinished )
        sendMessage(QString("Running"));
}

void MyNetworkCommunication::tellingFinishing()
{
    if ( !oppositeFinished )
        sendMessage(QString("Finishing"));
}

void MyNetworkCommunication::dealingMessage()
{
    while ( recvMessage() != QString("Finishing") )
    {

    }
    oppositeFinished = true;
}

void MyNetworkCommunication::sendMessage(const QString &text)
{
    messageToSend = text;
    QByteArray buffer = messageToSend.toUtf8();
    this->writeDatagram(buffer.constData(), buffer.size(), QHostAddress(ipAddress), port);
}

QString MyNetworkCommunication::recvMessage()
{
    static char buffer[MAX_BUFFER_LENGTH + 1];
    QHostAddress hostAddressBuffer;
    quint16 portBuffer;
    this->bind(port);
    qint64 bytesRecv = this->readDatagram(buffer, sizeof(buffer), &hostAddressBuffer, &portBuffer);
    buffer[bytesRecv] = '\0';

    if ( hostAddressBuffer == QHostAddress(ipAddress) && portBuffer == port )
    {
        messageRecving = QString::fromUtf8(buffer);
        return messageRecving;
    }
    else
        return QString();
}

void MyNetworkCommunication::startGame()
{
    oppositeFinished = false;
    ownFinished = false;
}

void MyNetworkCommunication::tellingMessage()
{
    while(!oppositeFinished )
    {
        if (ownFinished)
        {
            tellingFinishing();
            return;
        }
        else
            tellingRunning();
    }
}

