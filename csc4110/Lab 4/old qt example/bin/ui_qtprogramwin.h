/********************************************************************************
** Form generated from reading UI file 'qtprogramwin.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTPROGRAMWIN_H
#define UI_QTPROGRAMWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtProgramWin
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtProgramWin)
    {
        if (QtProgramWin->objectName().isEmpty())
            QtProgramWin->setObjectName(QStringLiteral("QtProgramWin"));
        QtProgramWin->resize(423, 265);
        centralWidget = new QWidget(QtProgramWin);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(70, 80, 75, 23));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(220, 80, 113, 20));
        QtProgramWin->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtProgramWin);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 423, 21));
        QtProgramWin->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtProgramWin);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtProgramWin->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtProgramWin);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtProgramWin->setStatusBar(statusBar);

        retranslateUi(QtProgramWin);

        QMetaObject::connectSlotsByName(QtProgramWin);
    } // setupUi

    void retranslateUi(QMainWindow *QtProgramWin)
    {
        QtProgramWin->setWindowTitle(QApplication::translate("QtProgramWin", "QtProgramWin", 0));
        pushButton->setText(QApplication::translate("QtProgramWin", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class QtProgramWin: public Ui_QtProgramWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTPROGRAMWIN_H
