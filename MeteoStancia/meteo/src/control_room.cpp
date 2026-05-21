#include <meteo/control_room.hpp>
#include <meteo/formats.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <cstring>         // для std::memcpy

// Подключаем asio (без отдельной компиляции, asio — header-only)
#define ASIO_STANDALONE    // Не использовать Boost, только asio
#include <asio.hpp>

using asio::ip::tcp;

namespace meteo {

ControlRoom::ControlRoom(const Params& params)
    : params_(params)   // Инициализируем поле params_ значением params
{
    std::cout << "ControlRoom created with " << params_.meteostations.size() 
              << " stations" << std::endl;
}

void ControlRoom::run() {
    // Бесконечный цикл опроса
    while (true) {
        std::cout << "\n=== Polling all stations ===\n" << std::endl;
        
        auto results = run_once();  // Один опрос
        
        // Выводим результаты в консоль
        for (const auto& info : results) {
            std::cout << info << std::endl;  // Использует наш operator<<
        }
        
        // Ждём 2 секунды перед следующим опросом
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

std::vector<MeteoInfo> ControlRoom::run_once() {
    std::vector<MeteoInfo> results;
    
    // Обходим ВСЕ станции из конфигурации
    for (const auto& station : params_.meteostations) {
        try {
            std::cout << "Connecting to " << station.description 
                      << " (" << station.ip << ":" << station.port << ")..." << std::endl;

            // ====== НАЧАЛО СЕТЕВОГО ВЗАИМОДЕЙСТВИЯ ======
            
            // 1. Создаём контекст ввода-вывода asio (ядро библиотеки)
            asio::io_context io_context;
            
            // 2. Создаём TCP-сокет
            tcp::socket socket(io_context);
            
            // 3. Преобразуем IP-адрес из строки в объект asio
            asio::ip::address ip_address = asio::ip::make_address(station.ip);
            
            // 4. Создаём endpoint (точку подключения) = IP + порт
            tcp::endpoint endpoint(ip_address, station.port);
            
            // 5. Подключаемся к серверу (синхронно — ждём соединения)
            socket.connect(endpoint);
            std::cout << "Connected!" << std::endl;
            
            // 6. Готовим буфер для приёма данных
            //    Размер = размеру структуры MeteoInfo
            std::vector<char> buffer(sizeof(MeteoInfo));
            
            // 7. Читаем данные от сервера (синхронно — ждём)
            //    asio::read читает ТОЧНО указанное количество байт
            size_t bytes_read = asio::read(socket, asio::buffer(buffer));
            
            std::cout << "Received " << bytes_read << " bytes" << std::endl;
            
            // 8. Преобразуем массив байтов обратно в структуру
            MeteoInfo info;
            std::memcpy(&info, buffer.data(), sizeof(MeteoInfo));
            
            // 9. Сохраняем результат
            results.push_back(info);
            
            // 10. Закрываем сокет (корректно завершаем соединение)
            socket.close();
            
        } catch (const std::exception& e) {
            // Если с этой станцией что-то пошло не так, пропускаем её
            std::cerr << "Error polling " << station.description 
                      << ": " << e.what() << std::endl;
            // Можно добавить "пустую" запись с информацией об ошибке
        }
    }
    
    return results;
}

} // namespace meteo