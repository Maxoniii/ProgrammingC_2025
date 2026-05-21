/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEditA;
    QLineEdit *lineEditB;
    QPushButton *btnPlus;
    QPushButton *btnMultiply;
    QPushButton *btnDivide;
    QPushButton *btnOst;
    QPushButton *btnCompare;
    QPushButton *btnPow;
    QPushButton *btnKoren;
    QPushButton *btnIncrPostA;
    QPushButton *btnIncrPreA;
    QLabel *labelResult;
    QLabel *labelError;
    QPushButton *btnIncrPreB;
    QPushButton *btnIncrPostB;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        lineEditA = new QLineEdit(centralwidget);
        lineEditA->setObjectName("lineEditA");
        lineEditA->setGeometry(QRect(80, 40, 251, 27));
        lineEditB = new QLineEdit(centralwidget);
        lineEditB->setObjectName("lineEditB");
        lineEditB->setGeometry(QRect(80, 80, 251, 27));
        btnPlus = new QPushButton(centralwidget);
        btnPlus->setObjectName("btnPlus");
        btnPlus->setGeometry(QRect(80, 180, 71, 61));
        btnMultiply = new QPushButton(centralwidget);
        btnMultiply->setObjectName("btnMultiply");
        btnMultiply->setGeometry(QRect(220, 180, 71, 61));
        btnDivide = new QPushButton(centralwidget);
        btnDivide->setObjectName("btnDivide");
        btnDivide->setGeometry(QRect(370, 180, 71, 61));
        btnOst = new QPushButton(centralwidget);
        btnOst->setObjectName("btnOst");
        btnOst->setGeometry(QRect(530, 180, 191, 151));
        btnCompare = new QPushButton(centralwidget);
        btnCompare->setObjectName("btnCompare");
        btnCompare->setGeometry(QRect(80, 270, 71, 61));
        btnPow = new QPushButton(centralwidget);
        btnPow->setObjectName("btnPow");
        btnPow->setGeometry(QRect(220, 270, 71, 61));
        btnKoren = new QPushButton(centralwidget);
        btnKoren->setObjectName("btnKoren");
        btnKoren->setGeometry(QRect(370, 270, 71, 61));
        btnIncrPostA = new QPushButton(centralwidget);
        btnIncrPostA->setObjectName("btnIncrPostA");
        btnIncrPostA->setGeometry(QRect(260, 360, 141, 61));
        btnIncrPreA = new QPushButton(centralwidget);
        btnIncrPreA->setObjectName("btnIncrPreA");
        btnIncrPreA->setGeometry(QRect(70, 360, 141, 61));
        labelResult = new QLabel(centralwidget);
        labelResult->setObjectName("labelResult");
        labelResult->setGeometry(QRect(440, 40, 351, 71));
        labelError = new QLabel(centralwidget);
        labelError->setObjectName("labelError");
        labelError->setGeometry(QRect(80, 460, 511, 19));
        btnIncrPreB = new QPushButton(centralwidget);
        btnIncrPreB->setObjectName("btnIncrPreB");
        btnIncrPreB->setGeometry(QRect(450, 360, 141, 61));
        btnIncrPostB = new QPushButton(centralwidget);
        btnIncrPostB->setObjectName("btnIncrPostB");
        btnIncrPostB->setGeometry(QRect(630, 360, 141, 61));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnPlus->setText(QCoreApplication::translate("MainWindow", "\320\237\320\273\321\216\321\201", nullptr));
        btnMultiply->setText(QCoreApplication::translate("MainWindow", "\320\243\320\274\320\275\320\276\320\266.", nullptr));
        btnDivide->setText(QCoreApplication::translate("MainWindow", "\320\224\320\265\320\273\320\265\320\275\320\270\320\265", nullptr));
        btnOst->setText(QCoreApplication::translate("MainWindow", "\320\236\321\201\321\202\320\260\321\202\320\276\320\272", nullptr));
        btnCompare->setText(QCoreApplication::translate("MainWindow", "\320\241\321\200\320\260\320\262\320\275\320\270\321\202\321\214", nullptr));
        btnPow->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\277\320\265\320\275\321\214", nullptr));
        btnKoren->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\321\200\320\265\320\275\321\214", nullptr));
        btnIncrPostA->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\321\202\320\230\320\275\320\272\321\200\320\265\320\274\320\265\320\275\321\202\320\220", nullptr));
        btnIncrPreA->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\265\320\230\320\275\320\272\321\200\320\265\320\274\320\265\320\275\321\202\320\220", nullptr));
        labelResult->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202:", nullptr));
        labelError->setText(QCoreApplication::translate("MainWindow", "\320\236\321\210\320\270\320\261\320\272\320\260:", nullptr));
        btnIncrPreB->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\265\320\230\320\275\320\272\321\200\320\265\320\274\320\265\320\275\321\202\320\222", nullptr));
        btnIncrPostB->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\321\202\320\230\320\275\320\272\321\200\320\265\320\274\320\265\320\275\321\202\320\222", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
