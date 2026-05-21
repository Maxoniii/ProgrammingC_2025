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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *labelErrorResult;
    QSpinBox *spinBoxSlbA;
    QTableWidget *tableA;
    QPushButton *btnCalculate;
    QTableWidget *tableRes;
    QSpinBox *spinBoxStrA;
    QPushButton *btnIncrResult;
    QSpinBox *spinBoxStrB;
    QSpinBox *spinBoxSlbB;
    QLabel *labelErrorA;
    QLabel *labelErrorB;
    QPushButton *btnIncrB;
    QPushButton *btnIncrA;
    QTableWidget *tableB;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("/* \320\223\320\273\320\260\320\262\320\275\320\276\320\265 \320\276\320\272\320\275\320\276 */\n"
"QMainWindow {\n"
"    background-color: #f0f4f8;\n"
"    border: 2px solid #2c3e50;\n"
"    border-radius: 8px;\n"
"}\n"
"\n"
"/* \320\227\320\260\320\263\320\276\320\273\320\276\320\262\320\276\320\272 \320\276\320\272\320\275\320\260 */\n"
"QMainWindow::title {\n"
"    background-color: #2c3e50;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"/* \320\232\320\275\320\276\320\277\320\272\320\270 */\n"
"QPushButton {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2980b9;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #1c6ea4;\n"
"}\n"
"\n"
"/* SpinBox */\n"
"QSpinBox {\n"
"    border: 2px solid #bdc3c7;\n"
"    border-radius: 4px;\n"
"    padding: 4px;\n"
"    background-color: white;\n"
""
                        "}\n"
"\n"
"/* \320\242\320\260\320\261\320\273\320\270\321\206\321\213 */\n"
"QTableWidget {\n"
"    gridline-color: #3498db;\n"
"    background-color: white;\n"
"    alternate-background-color: #f8f9fa;\n"
"    selection-background-color: #3498db;\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    padding: 5px;\n"
"    border: none;\n"
"}\n"
"\n"
"QTableWidget::item:selected {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"}\n"
"\n"
"/* \320\234\320\265\321\202\320\272\320\270 \320\276\321\210\320\270\320\261\320\276\320\272 */\n"
"QLabel {\n"
"    color: #e74c3c;\n"
"    font-weight: bold;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(20, 10, 731, 471));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        labelErrorResult = new QLabel(gridLayoutWidget);
        labelErrorResult->setObjectName("labelErrorResult");

        gridLayout->addWidget(labelErrorResult, 6, 1, 1, 2);

        spinBoxSlbA = new QSpinBox(gridLayoutWidget);
        spinBoxSlbA->setObjectName("spinBoxSlbA");
        spinBoxSlbA->setMaximum(1200);

        gridLayout->addWidget(spinBoxSlbA, 1, 1, 1, 1);

        tableA = new QTableWidget(gridLayoutWidget);
        tableA->setObjectName("tableA");

        gridLayout->addWidget(tableA, 2, 1, 1, 1);

        btnCalculate = new QPushButton(gridLayoutWidget);
        btnCalculate->setObjectName("btnCalculate");

        gridLayout->addWidget(btnCalculate, 4, 1, 1, 2);

        tableRes = new QTableWidget(gridLayoutWidget);
        tableRes->setObjectName("tableRes");

        gridLayout->addWidget(tableRes, 5, 1, 1, 2);

        spinBoxStrA = new QSpinBox(gridLayoutWidget);
        spinBoxStrA->setObjectName("spinBoxStrA");
        spinBoxStrA->setMaximum(1200);

        gridLayout->addWidget(spinBoxStrA, 0, 1, 1, 1);

        btnIncrResult = new QPushButton(gridLayoutWidget);
        btnIncrResult->setObjectName("btnIncrResult");

        gridLayout->addWidget(btnIncrResult, 5, 0, 1, 1);

        spinBoxStrB = new QSpinBox(gridLayoutWidget);
        spinBoxStrB->setObjectName("spinBoxStrB");
        spinBoxStrB->setMaximum(1200);

        gridLayout->addWidget(spinBoxStrB, 0, 2, 1, 1);

        spinBoxSlbB = new QSpinBox(gridLayoutWidget);
        spinBoxSlbB->setObjectName("spinBoxSlbB");
        spinBoxSlbB->setMaximum(1200);

        gridLayout->addWidget(spinBoxSlbB, 1, 2, 1, 1);

        labelErrorA = new QLabel(gridLayoutWidget);
        labelErrorA->setObjectName("labelErrorA");

        gridLayout->addWidget(labelErrorA, 3, 1, 1, 1);

        labelErrorB = new QLabel(gridLayoutWidget);
        labelErrorB->setObjectName("labelErrorB");

        gridLayout->addWidget(labelErrorB, 3, 2, 1, 1);

        btnIncrB = new QPushButton(gridLayoutWidget);
        btnIncrB->setObjectName("btnIncrB");

        gridLayout->addWidget(btnIncrB, 2, 4, 1, 1);

        btnIncrA = new QPushButton(gridLayoutWidget);
        btnIncrA->setObjectName("btnIncrA");

        gridLayout->addWidget(btnIncrA, 2, 0, 1, 1);

        tableB = new QTableWidget(gridLayoutWidget);
        tableB->setObjectName("tableB");

        gridLayout->addWidget(tableB, 2, 2, 1, 1);

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
        labelErrorResult->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        btnCalculate->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\207\320\270\321\201\320\273\320\270\321\202\321\214", nullptr));
        btnIncrResult->setText(QCoreApplication::translate("MainWindow", "\320\230\320\275\320\272.\320\240\320\265\320\267.", nullptr));
        labelErrorA->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        labelErrorB->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        btnIncrB->setText(QCoreApplication::translate("MainWindow", "\320\230\320\275\320\272\321\200\320\265\320\274\320\265\320\275\321\202 \320\222", nullptr));
        btnIncrA->setText(QCoreApplication::translate("MainWindow", " \320\230\320\275\320\272\321\200\320\265\320\274\320\265\320\275\321\202 \320\220 ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
