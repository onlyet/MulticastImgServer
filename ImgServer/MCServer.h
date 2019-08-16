#pragma once
#include <QObject>
#include <QHostAddress>

class QUdpSocket;

class MCServer : public QObject
{
    Q_OBJECT
public:
    explicit MCServer(const QString& groupAddress, unsigned short port, QObject* parent = Q_NULLPTR);
    ~MCServer();

    void sendDatagram(const QByteArray& data);
    void setTTL(int ttl);

signals:

    private slots :
        void run();
    void shutdown();

private:
    QUdpSocket*     m_socket;
    QHostAddress    m_hostAddress;
    unsigned short  m_port;
    bool            m_isRunning;
    char*           m_imgLenBuf;
};