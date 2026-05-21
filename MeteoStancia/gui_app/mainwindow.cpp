#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <meteo/control_room.hpp>
#include <meteo/utils.hpp>
#include <meteo/formats.hpp>
#include <QTimer>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QStatusBar>
#include <QDateTime>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Настройка таблицы
    ui->meteo_table->setColumnCount(5);
    ui->meteo_table->setHorizontalHeaderLabels(
        {"ID", "Температура", "Влажность", "Ветер", "Дата/время"});
    ui->meteo_table->horizontalHeader()->setStretchLastSection(true);

    // Настройка ТАЙМЕРА (НЕ запускаем сразу!)
    timer_ = std::make_unique<QTimer>(this);
    connect(timer_.get(), &QTimer::timeout, 
            this, &MainWindow::on_timer_timeout);
    // timer_->start() НЕ вызываем — галочка по умолчанию выключена

    // Инициализация ControlRoom
    try {
        meteo::ControlRoom::Params params;
        params.meteostations = meteo::read_configuration("config.json");
        room_ = std::make_unique<meteo::ControlRoom>(params);
        
        ui->statusbar->showMessage("Загружено станций: " + 
            QString::number(params.meteostations.size()));
            
    } catch (const std::exception& e) {
        ui->statusbar->showMessage("Ошибка инициализации: " + QString(e.what()));
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ===== ОБЩАЯ ФУНКЦИЯ ОПРОСА =====
void MainWindow::doPoll(bool clearOld)
{
    if (!room_) {
        ui->statusbar->showMessage("ControlRoom не инициализирован");
        return;
    }

    try {
        const auto infos = room_->run_once();
        
        if (clearOld) {
            ui->meteo_table->setRowCount(0);  // Очищаем для режима "Обновить"
        }
        
        QString currentTime = QDateTime::currentDateTime().toString("hh:mm:ss");
        
        for (const auto& info : infos) {
            int row = ui->meteo_table->rowCount();
            ui->meteo_table->insertRow(row);
            
            // ID
            ui->meteo_table->setItem(row, 0, 
                new QTableWidgetItem(QString::number(info.id)));
            
            // Температура
            ui->meteo_table->setItem(row, 1, 
                new QTableWidgetItem(QString::number(info.temp, 'f', 1) + "°C"));
            
            // Влажность
            ui->meteo_table->setItem(row, 2, 
                new QTableWidgetItem(QString::number(info.humidity, 'f', 1) + "%"));
            
            // Ветер
            ui->meteo_table->setItem(row, 3, 
                new QTableWidgetItem(QString::number(info.wind_velocity, 'f', 1) + " м/с"));
            
            // Дата/время
            QString datetime = QString("%1-%2-%3 %4:%5:%6")
                .arg(info.datetime.year)
                .arg(static_cast<int>(info.datetime.month), 2, 10, QChar('0'))
                .arg(static_cast<int>(info.datetime.day), 2, 10, QChar('0'))
                .arg(static_cast<int>(info.datetime.hour), 2, 10, QChar('0'))
                .arg(static_cast<int>(info.datetime.min), 2, 10, QChar('0'))
                .arg(static_cast<int>(info.datetime.sec), 2, 10, QChar('0'));
            ui->meteo_table->setItem(row, 4, new QTableWidgetItem(datetime));
        }
        
        ui->meteo_table->resizeColumnsToContents();
        ui->meteo_table->scrollToBottom();
        
        QString mode = clearOld ? "Обновлено" : "Добавлено";
        ui->statusbar->showMessage(
            QString("%1 записей: %2. Всего строк: %3")
                .arg(mode)
                .arg(infos.size())
                .arg(ui->meteo_table->rowCount()));
                
    } catch (const std::exception& e) {
        ui->statusbar->showMessage("Ошибка опроса: " + QString(e.what()));
        std::cerr << "Ошибка опроса: " << e.what() << std::endl;
    }
}

// ===== КНОПКА "ОПРОС СЕЙЧАС" =====
// Очищает таблицу и показывает актуальные данные
void MainWindow::on_bt_poll_clicked()
{
    doPoll(true);  // true = очистить перед выводом
}

// ===== КНОПКА "ОЧИСТИТЬ" =====
void MainWindow::on_bt_clear_clicked()
{
    ui->meteo_table->setRowCount(0);
    ui->statusbar->showMessage("Таблица очищена");
}

// ===== ГАЛОЧКА АВТООПРОСА =====
void MainWindow::on_cb_autopoll_stateChanged(int state)
{
    if (state == Qt::Checked) {
        // Включаем автоопрос
        timer_->start(2000);  // Каждые 2 секунды
        ui->statusbar->showMessage("Автоопрос ВКЛЮЧЕН (интервал: 2 сек)");
        ui->bt_poll->setEnabled(false);  // Блокируем кнопку ручного опроса
    } else {
        // Выключаем автоопрос
        timer_->stop();
        ui->statusbar->showMessage("Автоопрос ВЫКЛЮЧЕН");
        ui->bt_poll->setEnabled(true);   // Разблокируем кнопку
    }
}

// ===== СЛОТ ТАЙМЕРА (ДЛЯ АВТООПРОСА) =====
// Добавляет строки, не очищая таблицу
void MainWindow::on_timer_timeout()
{
    doPoll(false);  // false = не очищать, добавляем в историю
}