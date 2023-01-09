cmake_minimum_required(VERSION 3.16)
project(
    libws
    LANGUAGES CXX
)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets)

file(GLOB CODE ${PROJECT_SOURCE_DIR}/*.cpp ${PROJECT_SOURCE_DIR}/*.h)

qt_add_library(libws ${CODE})

target_link_libraries(libws PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::OpenGLWidgets
)
