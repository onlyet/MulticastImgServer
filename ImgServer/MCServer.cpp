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
}

void MCServer::sendDatagram(const QByteArray& data)
{
    m_socket->writeDatagram(data, m_hostAddress, m_port);
}

void MCServer::setTTL(int ttl)
{
    m_socket->setSocketOption(QAbstractSocket::MulticastTtlOption, ttl);
}

void MCServer::shutdown()
{
    m_isRunning = false;
}

void MCServer::run()
{
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
        sprintf(m_imgLenBuf, "newImage:%d", imgLen);

        m_socket->writeDatagram(m_imgLenBuf, strlen(m_imgLenBuf), m_hostAddress, m_port);
        //�ȴ����ݰ�����
        m_socket->waitForBytesWritten();

        int sentLen = 0;    //�ѷ�����
        int sendingLen;     //����ʵ�ʷ��ͳ���
        for (; sentLen < imgLen; sentLen += sendingLen)
        {
            if (imgLen - sentLen >= MC_SEND_BUF_LEN)
                sendingLen = MC_SEND_BUF_LEN;
            else
                sendingLen = imgLen - sentLen;

            m_socket->writeDatagram(pImg, sendingLen, m_hostAddress, m_port);
            m_socket->waitForBytesWritten();
        }
    }
}
