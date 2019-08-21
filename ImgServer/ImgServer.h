#pragma once

#include <QtWidgets/QWidget>
#include "ui_ImgServer.h"

class MCServer;

class ImgServer : public QWidget
{
    Q_OBJECT

public:
    ImgServer(QWidget *parent = Q_NULLPTR);
    ~ImgServer();

    void start();

signals:
    void startServer();
    //void run();

private:
    Ui::ImgServerClass  ui;
    MCServer*           m_imgServer;
    QThread*            m_imgThread;
};
