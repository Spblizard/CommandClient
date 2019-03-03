#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    m_udp = new QUdpSocket();
    m_udp->bind(QHostAddress::Any, 11001);
    connect(m_udp, &QUdpSocket::readyRead, this, &Client::readDatagram);
    getAddress();
}

void Client::sendDatagram()
{
   QByteArray arr("test for datagram router");
   getAddress();
   QNetworkDatagram datagram(arr, m_localAddress, 11002);
   m_udp->writeDatagram(datagram);
}

void Client::getAddress()
{
    const QHostAddress address;
    foreach (QHostAddress address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress::LocalHost)
            m_localAddress = address;
    }

    QString str = m_localAddress.toString();
    QStringList strList = str.split(".");
    strList[3] = "255";
    str = strList.join(".");
    m_localAddress.setAddress(str);
}

void Client::readDatagram()
{
    QNetworkDatagram datagram = m_udp->receiveDatagram();
    QByteArray arr = datagram.data();
    QString str;
    QDataStream stream(&arr, QIODevice::ReadOnly);
    stream.setVersion(QDataStream::Qt_5_9);
    stream >> str;
    m_listHost << datagram.senderAddress();
    emit signalToQmlHost(str);
}

void Client::connectHost(int index)
{
    m_client = new QTcpSocket(this);
    connect(m_client, &QTcpSocket::connected, this, &Client::slotConnected);
    connect(m_client, &QTcpSocket::disconnected, m_client, &Client::deleteLater);
    connect(m_client, SIGNAL (disconnected()), this, SLOT (slotDisconnected()));
    m_client->connectToHost(m_listHost[0], 11000);
}

void Client::sendCommand(QString command)
{
   QByteArray arr;
   QDataStream stream (&arr, QIODevice::WriteOnly);
   stream.setVersion(QDataStream::Qt_5_9);
   stream << quint16(0) << command;
   m_client->write(arr);
   m_client->flush();
}

void Client::slotConnected()
{
    qDebug() << "Connected";
    emit signalToQmlConnect();
}

void Client::slotDisconnected()
{
    qDebug() << "Disconnected";
    emit signalToQmlDisconnect();
}

