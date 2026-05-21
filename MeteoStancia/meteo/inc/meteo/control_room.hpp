#pragma once
#include <vector>
#include <meteo/types.hpp>
#include <meteo/formats.hpp>

namespace meteo {

class ControlRoom {
public:
    struct Params {
        std::vector<Meteostation> meteostations;
    };

    explicit ControlRoom(const Params& params);

    // Запускает БЕСКОНЕЧНЫЙ опрос (для консольного клиента)
    void run();

    // Запускает ОДИН цикл опроса всех станций (для GUI)
    std::vector<MeteoInfo> run_once();

private:
    const Params params_;  // Храним параметры
};

} // namespace meteo