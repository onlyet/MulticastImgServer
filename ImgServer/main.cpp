#include "ImgServer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImgServer w;
    //w.show();
    w.start();

    return a.exec();
}
