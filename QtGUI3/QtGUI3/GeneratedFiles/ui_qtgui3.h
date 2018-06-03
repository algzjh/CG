/********************************************************************************
** Form generated from reading UI file 'qtgui3.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUI3_H
#define UI_QTGUI3_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGUI3Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtGUI3Class)
    {
        if (QtGUI3Class->objectName().isEmpty())
            QtGUI3Class->setObjectName(QStringLiteral("QtGUI3Class"));
        QtGUI3Class->resize(600, 400);
        menuBar = new QMenuBar(QtGUI3Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        QtGUI3Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtGUI3Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtGUI3Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtGUI3Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QtGUI3Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtGUI3Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtGUI3Class->setStatusBar(statusBar);

        retranslateUi(QtGUI3Class);

        QMetaObject::connectSlotsByName(QtGUI3Class);
    } // setupUi

    void retranslateUi(QMainWindow *QtGUI3Class)
    {
        QtGUI3Class->setWindowTitle(QApplication::translate("QtGUI3Class", "QtGUI3", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtGUI3Class: public Ui_QtGUI3Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUI3_H
