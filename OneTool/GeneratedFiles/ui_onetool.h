/********************************************************************************
** Form generated from reading UI file 'onetool.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONETOOL_H
#define UI_ONETOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OneToolClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OneToolClass)
    {
        if (OneToolClass->objectName().isEmpty())
            OneToolClass->setObjectName(QStringLiteral("OneToolClass"));
        OneToolClass->resize(1402, 960);
        centralWidget = new QWidget(OneToolClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(1290, 380, 101, 41));
        QFont font;
        font.setPointSize(13);
        pushButton->setFont(font);
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(1290, 620, 101, 41));
        pushButton_2->setFont(font);
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(1290, 170, 101, 41));
        QFont font1;
        font1.setPointSize(12);
        pushButton_3->setFont(font1);
        OneToolClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(OneToolClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1402, 23));
        OneToolClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(OneToolClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        OneToolClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(OneToolClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        OneToolClass->setStatusBar(statusBar);

        retranslateUi(OneToolClass);
        QObject::connect(pushButton_3, SIGNAL(clicked()), OneToolClass, SLOT(openImgFile()));
        QObject::connect(pushButton, SIGNAL(clicked()), OneToolClass, SLOT(openTemFile()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), OneToolClass, SLOT(saveTemplate()));

        QMetaObject::connectSlotsByName(OneToolClass);
    } // setupUi

    void retranslateUi(QMainWindow *OneToolClass)
    {
        OneToolClass->setWindowTitle(QApplication::translate("OneToolClass", "OneTool", 0));
        pushButton->setText(QApplication::translate("OneToolClass", "\345\257\274\345\205\245\346\250\241\346\235\277", 0));
        pushButton_2->setText(QApplication::translate("OneToolClass", "\345\257\274\345\207\272\346\250\241\346\235\277", 0));
        pushButton_3->setText(QApplication::translate("OneToolClass", "\346\211\223\345\274\200\345\233\276\345\203\217", 0));
    } // retranslateUi

};

namespace Ui {
    class OneToolClass: public Ui_OneToolClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONETOOL_H
