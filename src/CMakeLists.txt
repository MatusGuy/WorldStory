cmake_minimum_required(VERSION 3.16)
project(
    WSGame
    VERSION 0.0.0.0
)

set(CMAKE_AUTOMOC ON)
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets)

qt_add_resources(QRC ./assets/assets.qrc)

qt_add_executable(WSGame main.cpp ${QRC})

add_subdirectory(${PROJECT_SOURCE_DIR}/classes)
target_link_libraries(WSGame PUBLIC libws)

target_compile_definitions(WSGame PUBLIC __WS_NAME__=\"${PROJECT_NAME}\")
target_compile_definitions(WSGame PUBLIC __WS_VERSION__=\"${PROJECT_VERSION}\")

target_include_directories(WSGame PUBLIC ${PROJECT_BINARY_DIR})

#target_include_directories(WSGame PUBLIC classes/)
