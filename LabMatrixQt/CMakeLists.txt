cmake_minimum_required(VERSION 3.16)

project(LabMatrixQt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# ===== ДОБАВЛЯЕМ НАШУ БИБЛИОТЕКУ =====
# Путь к библиотеке MatrixLib (исправьте путь если нужно)
add_subdirectory(../MatrixLib MatrixLib_build)
# ====================================

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        # matrix.hpp и matrix.cpp УДАЛЯЕМ отсюда - они теперь в библиотеке
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(LabMatrixQt
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        # matrix.hpp matrix.cpp НЕ ДОБАВЛЯЕМ СЮДА
    )
else()
    if(ANDROID)
        add_library(LabMatrixQt SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(LabMatrixQt
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Линкуем с нашей библиотекой И Qt
target_link_libraries(LabMatrixQt PRIVATE
    MatrixLib                    # НАША БИБЛИОТЕКА
    Qt${QT_VERSION_MAJOR}::Widgets
)

# Добавляем путь к заголовкам библиотеки
target_include_directories(LabMatrixQt PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../Матрица/MatrixLib  # для matrix.hpp
)

# Остальная часть файла без изменений...
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.LabMatrixQt)
endif()
set_target_properties(LabMatrixQt PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS LabMatrixQt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(LabMatrixQt)
endif()
