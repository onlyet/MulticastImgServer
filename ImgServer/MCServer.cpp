#include "MCServer.h"
#include <QUdpSocket>
#include <QApplication>
#include <QScreen>
#include <QPixmap>
#include <QBuffer>

#define MC_SEND_BUF_LEN 4000
#define MC_IMG_LEN_BUF_LEN 32

MCServer::MCServer(const QString& groupAddress, unsigned short port, QObject* parent)
    : m_hostAddress(groupAddress)
    , m_port(port)
    , m_isRunning(false)
{
    m_imgLenBuf = new char[MC_IMG_LEN_BUF_LEN];
}


MCServer::~MCServer()
{
    delete[] m_imgLenBuf;
}

void MCServer::sendDatagram(const QByteArray& data)
{
    m_socket->writeDatagram(data, m_hostAddress, m_port);
}

void MCServer::setTTL(int ttl)
{
    m_socket->setSocketOption(QAbstractSocket::MulticastTtlOption, ttl);
}

//void MCServer::start()
//{
//    m_socket = new QUdpSocket(this);
//}


void MCServer::shutdown()
{
    m_isRunning = false;
}

void MCServer::run()
{
    m_socket = new QUdpSocket(this);

    setTTL(5);

    m_isRunning = true;

    while (m_isRunning)
    {
        QPixmap pixmap = QApplication::primaryScreen()->grabWindow(0);
        QByteArray ba;
        QBuffer buffer(&ba);
        if (buffer.open(QIODevice::WriteOnly))
        {
            pixmap.save(&buffer, "JPG", 35);
        }
        const char* pImg = ba.constData();
        int imgLen = ba.length();
        qDebug() << "image len: " << imgLen;
        sprintf(m_imgLenBuf, "newImage:%d", imgLen);

        //发送图片长度
        m_socket->writeDatagram(m_imgLenBuf, strlen(m_imgLenBuf), m_hostAddress, m_port);
        //等待数据包发出
        m_socket->waitForBytesWritten();

        int sentLen = 0;    //已发长度
        int sendingLen;     //本次实际发送长度
        for (; sentLen < imgLen; sentLen += sendingLen)
        {
            if (imgLen - sentLen >= MC_SEND_BUF_LEN)
                sendingLen = MC_SEND_BUF_LEN;
            else
                sendingLen = imgLen - sentLen;

            m_socket->writeDatagram(pImg + sentLen, sendingLen, m_hostAddress, m_port);
            m_socket->waitForBytesWritten();
        }
    }
}
