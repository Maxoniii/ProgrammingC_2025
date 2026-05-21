cmake_minimum_required(VERSION 3.16)
project(LabCalculator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


add_subdirectory(../CalculatorLib CalculatorLib_build)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

# Создание исполняемого файла
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(LabCalculator
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(LabCalculator SHARED ${PROJECT_SOURCES})
    else()
        add_executable(LabCalculator ${PROJECT_SOURCES})
    endif()
endif()

# ==== ПОДКЛЮЧЕНИЕ БИБЛИОТЕК И Qt ====
target_link_libraries(LabCalculator PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    CalculatorLib  # имя вашей библиотеки (должно совпадать с target_name в CalculatorLib/CMakeLists.txt)
)

# Добавляем путь к заголовкам библиотеки
target_include_directories(LabCalculator PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../CalculatorLib  # для matrix.hpp
)

# ==== НАСТРОЙКИ ПЛАТФОРМЫ ====
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.LabCalculator)
endif()
set_target_properties(LabCalculator PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# ==== УСТАНОВКА ====
include(GNUInstallDirs)
install(TARGETS LabCalculator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Финализация для Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(LabCalculator)
endif()
