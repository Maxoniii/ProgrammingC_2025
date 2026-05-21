cmake_minimum_required(VERSION 3.15)

# Корневой проект
project(meteo_project LANGUAGES CXX)

# Подпроекты (будут собраны все вместе)
add_subdirectory(meteo)            # Сначала библиотека (другие от неё зависят)
add_subdirectory(synchro_server)   # Сервер
add_subdirectory(synchro_client)   # Консольный клиент
add_subdirectory(gui_app)          # GUI-клиент