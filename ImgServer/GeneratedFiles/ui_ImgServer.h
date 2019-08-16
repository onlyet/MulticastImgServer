/********************************************************************************
** Form generated from reading UI file 'ImgServer.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMGSERVER_H
#define UI_IMGSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImgServerClass
{
public:

    void setupUi(QWidget *ImgServerClass)
    {
        if (ImgServerClass->objectName().isEmpty())
            ImgServerClass->setObjectName(QStringLiteral("ImgServerClass"));
        ImgServerClass->resize(600, 400);

        retranslateUi(ImgServerClass);

        QMetaObject::connectSlotsByName(ImgServerClass);
    } // setupUi

    void retranslateUi(QWidget *ImgServerClass)
    {
        ImgServerClass->setWindowTitle(QApplication::translate("ImgServerClass", "ImgServer", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ImgServerClass: public Ui_ImgServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMGSERVER_H
