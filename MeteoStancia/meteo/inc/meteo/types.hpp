#pragma once          // Защита от двойного включения. Аналог #ifndef #define #endif
#include <string>     // Для std::string

namespace meteo {     // Все наши типы будут в пространстве имён meteo, чтобы не было конфликтов имён

struct Meteostation {         // Структура описывает ОДНУ метеостанцию (читается из config.json)
    std::string ip;           // IP-адрес для подключения, например "127.0.0.1"
    std::string description;  // Название, например "Baltiisk"
    unsigned short port;      // Номер порта, например 7000
};

} // namespace meteo