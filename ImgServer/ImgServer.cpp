#include "ImgServer.h"
#include "MCServer.h"
#include <QThread>

ImgServer::ImgServer(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

ImgServer::~ImgServer()
{
    m_imgServer->shutdown();
    m_imgThread->quit();
    m_imgThread->wait();
}

void ImgServer::start()
{
    m_imgThread = new QThread(this);
    m_imgServer = new MCServer("224.55.55.55", 7777);

    //connect(this, &ImgServer::run, m_imgServer, &MCServer::run);
    connect(m_imgThread, SIGNAL(started()), m_imgServer, SLOT(run()));
    //connect(this, SIGNAL(run()), m_imgServer, SLOT(run()));
    connect(m_imgThread, SIGNAL(finished()), m_imgServer, SLOT(deleteLater()));

    m_imgServer->moveToThread(m_imgThread);
    m_imgThread->start();

    //emit run();
}
