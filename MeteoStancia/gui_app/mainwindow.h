#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QTimer>

namespace meteo {
    class ControlRoom;
}

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_bt_poll_clicked();          // Кнопка "Опрос сейчас"
    void on_bt_clear_clicked();         // Кнопка "Очистить"
    void on_cb_autopoll_stateChanged(int state);  // Галочка автоопроса
    void on_timer_timeout();            // Слот для таймера

private:
    void doPoll(bool clearOld);         // Общая функция опроса
    
    Ui::MainWindow *ui;
    std::unique_ptr<meteo::ControlRoom> room_;
    std::unique_ptr<QTimer> timer_;
};

#endif // MAINWINDOW_H