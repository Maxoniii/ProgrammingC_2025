#include <iostream>
#include <meteo/control_room.hpp>
#include <meteo/utils.hpp>

int main() {
    try {
        std::cout << "=== Console Weather Client ===" << std::endl;
        
        // 1. Читаем конфигурацию
        meteo::ControlRoom::Params params;
        params.meteostations = meteo::read_configuration("config.json");
        
        std::cout << "Loaded " << params.meteostations.size() 
                  << " stations from config" << std::endl;
        
        // 2. Создаём центр управления
        meteo::ControlRoom room(params);
        
        // 3. Запускаем бесконечный опрос (будет работать, пока не нажмём Ctrl+C)
        room.run();
        
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}