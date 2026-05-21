#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "matrix.hpp"
#include<QTableWidget>
#include<QTableWidgetItem>
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
    void onSpinBoxStrAChanged(int str);
    void onSpinBoxSlbAChanged(int slb);
    void onSpinBoxStrBChanged(int str);
    void onSpinBoxSlbBChanged(int slb);

    void onTableItemChanged(QTableWidgetItem *item);

    void onCalculateClicked();
    void onIncrementAClicked();
    void onIncrementBClicked();
    void onIncrementResultClicked();
private:
    Ui::MainWindow *ui;

    void setupConnections();
    void resizeTable(QTableWidget *table, int str,int slb);
    void fillTableFromMatrix(QTableWidget *table, const mt::matrix &mat);
    mt::matrix readMat(QTableWidget *table,bool &ok)const;
    bool validateAll();
};
#endif
