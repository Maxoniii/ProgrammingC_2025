cmake_minimum_required(VERSION 3.15)   # Минимальная версия CMake

set(PROJECT_NAME meteo)                # Задаём переменную с именем проекта
project("${PROJECT_NAME}" LANGUAGES CXX) # Создаём проект на C++

set(CMAKE_CXX_STANDARD 20)             # Используем стандарт C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON)    # Обязательно требуем C++20 (ошибка, если компилятор не поддерживает)

# Подключаем пути к заголовочным файлам ВНЕШНИХ библиотек
# asio/include — путь к основной библиотеке asio
include_directories("../ext/asio/include")
# ext — путь к nlohmann/json.hpp (лежит прямо в ext)
include_directories("../ext")

# Создаём СТАТИЧЕСКУЮ библиотеку (статическая — вкомпилируется в исполняемый файл)
add_library("${PROJECT_NAME}" STATIC 
    inc/meteo/formats.hpp    # Заголовочные файлы тоже указываем,
    inc/meteo/types.hpp      # чтобы они отображались в IDE
    inc/meteo/utils.hpp  
    inc/meteo/control_room.hpp
    src/utils.cpp            # Исходники для компиляции
    src/control_room.cpp
)

# Говорим CMake: "Папка inc содержит публичные заголовки библиотеки"
# PUBLIC означает, что любой, кто линкуется с meteo, будет ВИДЕТЬ эти заголовки
# и ему не нужно вручную добавлять include_directories("meteo/inc")
target_include_directories("${PROJECT_NAME}" PUBLIC inc)