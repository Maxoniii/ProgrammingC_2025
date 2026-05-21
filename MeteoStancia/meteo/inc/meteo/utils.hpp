#pragma once
#include <vector>          // Для std::vector
#include <string>          // Для std::string
#include <meteo/types.hpp> // Нам нужна структура Meteostation

namespace meteo {

// Функция читает JSON-файл и возвращает список метеостанций
std::vector<meteo::Meteostation> read_configuration(const std::string& filename);

} // namespace meteo