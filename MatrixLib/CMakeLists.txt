cmake_minimum_required(VERSION 3.16)
project(MatrixLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Файлы в текущей папке
set(SOURCES
    matrix.cpp
)

set(HEADERS
    matrix.hpp
)

# Проверяем существование файлов
foreach(FILE ${SOURCES} ${HEADERS})
    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${FILE})
        message(FATAL_ERROR "File ${FILE} not found in ${CMAKE_CURRENT_SOURCE_DIR}")
    endif()
endforeach()

# Создаём статическую библиотеку
add_library(MatrixLib STATIC ${SOURCES} ${HEADERS})

# Указываем путь к заголовкам
target_include_directories(MatrixLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
