#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QNetworkDatagram>
#include <QNetworkInterface>
#include <QDataStream>
#include <qhostaddress.h>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

private:
    QUdpSocket *m_udp;
    QTcpSocket *m_client;
    QHostAddress mServer;
    QHostAddress m_localAddress;
    quint16 mNextBlockSize;

signals:
    void signalToQmlHost(const QString &str);

public slots:
    void readDatagram();
    void readClient();
    void sendDatagram();
    void getAddress();
    void connectHost();
    void sendCommand(const QString &);
    virtual void slotConnected();
    virtual void slotDisconnected();
};

#endif // CLIENT_H
