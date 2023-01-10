cmake_minimum_required(VERSION 3.16)
project(
    libws
    LANGUAGES CXX
)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets)

file(GLOB CODE ${PROJECT_SOURCE_DIR}/*.cpp ${PROJECT_SOURCE_DIR}/*.h)

qt_add_library(libws STATIC ${CODE})
set_target_properties(libws PROPERTIES OUTPUT_NAME "libws")

target_link_libraries(libws PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::OpenGLWidgets
)

target_include_directories(WSGame PUBLIC ${PROJECT_BINARY_DIR})