#define ASIO_STANDALONE    // Используем asio без Boost

#include <asio.hpp>
#include <iostream>
#include <cstdlib>         // для rand()
#include <ctime>           // для time()
#include <cstring>         // для memcpy
#include <thread>
#include <chrono>

// Подключаем наши общие структуры
#include <meteo/formats.hpp>

using namespace std::chrono_literals;  // Можно писать 100ms вместо std::chrono::milliseconds(100)

/**
 * Подготавливает случайные данные о погоде для станции с заданным ID.
 */
meteo::MeteoInfo prepare_meteo_info(const size_t station_id) {
    meteo::MeteoInfo info;
    info.id = station_id;
    
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm* tm = std::localtime(&t);
    info.datetime.year = tm->tm_year + 1900;
    info.datetime.month = tm ->tm_mon +1;
    info.datetime.day = tm -> tm_mday;
    info.datetime.hour = tm -> tm_hour;
    info.datetime.min = tm -> tm_min;
    info.datetime.sec = tm -> tm_sec;
    

    info.temp = 15.0f + (rand() % 200) * 0.1f;     // 15.0 .. 34.9
    info.humidity = 40.0f + (rand() % 400) * 0.1f; // 40.0 .. 79.9
    info.wind_velocity = (rand() % 100) * 0.1f;     // 0.0 .. 9.9

    return info;
}

/**
 * Преобразует структуру MeteoInfo в массив байтов для отправки по сети.
 */
std::vector<char> to_bytes_array(const meteo::MeteoInfo& info) {
    std::vector<char> vec(sizeof(meteo::MeteoInfo));
    // Копируем байты из структуры в вектор
    std::memcpy(vec.data(), &info, sizeof(meteo::MeteoInfo));
    return vec;
}

int main(int argc, char** argv) {
    // Проверяем аргументы командной строки
    if (argc < 3) {
        std::cout << "Usage: synchro_server <port> <station_id>\n";
        std::cout << "Example: synchro_server 7000 1\n";
        return -1;
    }

    try {
        unsigned short port = std::stoi(argv[1]);   // Первый аргумент — порт
        const size_t station_id = std::stoull(argv[2]); // Второй аргумент — ID станции

        // Инициализируем генератор случайных чисел
        std::srand(static_cast<unsigned>(std::time(nullptr)) + station_id);

        // Создаём контекст asio
        asio::io_context io_context;
        
        // Создаём endpoint: слушать все интерфейсы (v4()), на указанном порту
        asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), port);
        
        // Acceptor — "слушатель", ожидает входящие соединения
        asio::ip::tcp::acceptor acceptor(io_context, endpoint);
        
        std::cout << "Weather station #" << station_id 
                  << " started on port " << port << std::endl;
        
        // Бесконечный цикл обработки клиентов
        while (true) {
            std::cout << "Waiting for client connection..." << std::endl;
            
            // Создаём сокет для нового клиента
            asio::ip::tcp::socket socket(io_context);
            
            // accept() — БЛОКИРУЕТСЯ, пока клиент не подключится
            acceptor.accept(socket);
            
            std::cout << "Client connected! Preparing weather data..." << std::endl;
            
            // Генерируем данные о погоде
            const auto weather_info = prepare_meteo_info(station_id);
            const auto output_buf = to_bytes_array(weather_info);
            
            // Отправляем данные клиенту
            // asio::write отправляет ВСЕ данные из буфера
            asio::write(socket, asio::buffer(output_buf));
            
            std::cout << "Data sent (temp=" << weather_info.temp 
                      << "°, humidity=" << weather_info.humidity << "%)" << std::endl;
            
            // Небольшая пауза перед закрытием соединения
            std::this_thread::sleep_for(100ms);
            
            // Закрываем сокет — соединение разрывается
            socket.close();
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}