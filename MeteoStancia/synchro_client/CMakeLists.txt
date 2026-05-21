cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME synchro_client)
project("${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

# Подключаем пути к внешним библиотекам
include_directories("../ext/asio/include")
include_directories("../ext")

add_executable("${PROJECT_NAME}" client.cpp)

# Линкуемся с meteo
target_link_libraries("${PROJECT_NAME}" PRIVATE meteo)

# Копируем config.json в папку с исполняемым файлом при сборке
file(COPY config.json DESTINATION ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/Debug)