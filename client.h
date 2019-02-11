#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QNetworkDatagram>
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

signals:
    void signalToQmlHost(QString str);
    void signalToQmlConnect();
    void signalToQmlDisconnect();

public slots:
    void readDatagram();
    void sendDatagram();
    void connectHost(int);
    void sendCommand(QString);
    virtual void slotConnected();
    virtual void slotDisconnected();
};

#endif // CLIENT_H
