#pragma once

#include <QtWidgets/QWidget>
#include "ui_ImgServer.h"

class ImgServer : public QWidget
{
    Q_OBJECT

public:
    ImgServer(QWidget *parent = Q_NULLPTR);

private:
    Ui::ImgServerClass ui;
};
