#include <meteo/utils.hpp>   // Свой заголовок
#include <fstream>           // Для чтения файлов (std::ifstream)
#include <stdexcept>         // Для std::runtime_error (исключения)
#include <nlohmann/json.hpp> // Библиотека для работы с JSON (лежит в ext/)
#include <iostream>          // Для отладки

using json = nlohmann::json; // Сокращаем имя, чтобы не писать nlohmann::json каждый раз

namespace meteo {

std::vector<Meteostation> read_configuration(const std::string& filename) {
    // 1. Открываем файл
    std::ifstream in(filename);
    if (!in.is_open()) {
        // Если не открылся — кидаем исключение (ошибка)
        throw std::runtime_error("Config file not found: " + filename);
    }

    // 2. Парсим JSON из файла
    json data;
    try {
        data = json::parse(in);  // Читаем весь файл и разбираем как JSON
    } catch (const std::exception& e) {
        throw std::runtime_error("JSON parse error: " + std::string(e.what()));
    }

    // 3. Проверяем, что data — это массив
    if (!data.is_array()) {
        throw std::runtime_error("Config JSON must be an array");
    }

    // 4. Создаём вектор и резервируем память (оптимизация)
    std::vector<Meteostation> meteostations;
    meteostations.reserve(data.size());

    // 5. Проходим по всем элементам массива
    for (const auto& elem : data) {
        Meteostation ms;
        ms.ip = elem.at("ip").get<std::string>();               // Поле "ip" как строка
        ms.port = elem.at("port").get<unsigned short>();        // Поле "port" как число
        ms.description = elem.at("description").get<std::string>(); // Поле "description"
        meteostations.push_back(std::move(ms));  // Добавляем в конец вектора (move — перемещаем, не копируем строки)
    }

    return meteostations;
}

} // namespace meteo