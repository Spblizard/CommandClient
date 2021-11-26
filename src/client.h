#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QNetworkDatagram>
#include <QNetworkInterface>
#include <QDataStream>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

private:
    QUdpSocket *m_udp;
    QTcpSocket *m_client;
    QList<QHostAddress> m_listHost;
    QHostAddress m_localAddress;

signals:
    void signalToQmlHost(QString str);
    void signalToQmlConnect();
    void signalToQmlDisconnect();

public slots:
    void readDatagram();
    void sendDatagram();
    void getAddress();
    void connectHost(int);
    void sendCommand(QString);
    virtual void slotConnected();
    virtual void slotDisconnected();
};

#endif // CLIENT_H
