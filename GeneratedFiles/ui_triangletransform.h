/********************************************************************************
** Form generated from reading UI file 'triangletransform.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRIANGLETRANSFORM_H
#define UI_TRIANGLETRANSFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TriangleTransformClass
{
public:
    QAction *actionOpenImage;
    QAction *actionTransform;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *TriangleTransformClass)
    {
        if (TriangleTransformClass->objectName().isEmpty())
            TriangleTransformClass->setObjectName(QStringLiteral("TriangleTransformClass"));
        TriangleTransformClass->resize(1304, 725);
        actionOpenImage = new QAction(TriangleTransformClass);
        actionOpenImage->setObjectName(QStringLiteral("actionOpenImage"));
        actionTransform = new QAction(TriangleTransformClass);
        actionTransform->setObjectName(QStringLiteral("actionTransform"));
        centralWidget = new QWidget(TriangleTransformClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        TriangleTransformClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TriangleTransformClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1304, 23));
        TriangleTransformClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TriangleTransformClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TriangleTransformClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        mainToolBar->addAction(actionOpenImage);
        mainToolBar->addAction(actionTransform);

        retranslateUi(TriangleTransformClass);

        QMetaObject::connectSlotsByName(TriangleTransformClass);
    } // setupUi

    void retranslateUi(QMainWindow *TriangleTransformClass)
    {
        TriangleTransformClass->setWindowTitle(QApplication::translate("TriangleTransformClass", "TriangleTransform", 0));
        actionOpenImage->setText(QApplication::translate("TriangleTransformClass", "openImage", 0));
        actionTransform->setText(QApplication::translate("TriangleTransformClass", "transform", 0));
    } // retranslateUi

};

namespace Ui {
    class TriangleTransformClass: public Ui_TriangleTransformClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRIANGLETRANSFORM_H
