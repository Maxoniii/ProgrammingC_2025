cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME synchro_server)
project("${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# На Windows часто нужна эта настройка для корректной работы с потоками
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

# Подключаем asio (сервер тоже его использует)
include_directories("../ext/asio/include")

# Создаём исполняемый файл
add_executable("${PROJECT_NAME}" server.cpp)

# Линкуемся с нашей библиотекой meteo
target_link_libraries("${PROJECT_NAME}" PRIVATE meteo)