#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>

#include "bigint.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_btnPlus_clicked();
    void on_btnMultiply_clicked();
    void on_btnIncrPreA_clicked();
    void on_btnIncrPostA_clicked();
    void on_btnIncrPreB_clicked();
    void on_btnIncrPostB_clicked();
    void on_btnDivide_clicked();
    void on_btnOst_clicked();
    void on_btnPow_clicked();
    void on_btnKoren_clicked();
    void on_btnCompare_clicked();

    void on_lineEditA_textChanged(const QString &text);
    void on_lineEditB_textChanged(const QString &text);



private:
    Ui::MainWindow *ui;

    bool getBigIntFromLineEdit(QLineEdit* edit, BigInt& num, QString& error);
    void clearMessages();
};
#endif // MAINWINDOW_H
