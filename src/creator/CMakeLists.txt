cmake_minimum_required(VERSION 3.16)
project(
    WSCreator
    VERSION 0.0.0.0
)

set(CMAKE_AUTOMOC ON)
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets)

file(GLOB FORMS assets/interface/*.ui)
qt_wrap_ui(UI ${FORMS})

file(GLOB_RECURSE CODE classes/*.cpp classes/*.h)
list(APPEND CODE main.cpp)

qt_add_resources(QRC assets/creator.qrc)
qt_add_resources(QRC ../assets/assets.qrc)

if(NOT "${CMAKE_SYSTEM}" MATCHES "Linux")
    qt_add_resources(QRC assets/icons/icons.qrc)
endif()

message("rcc: ${QRC}")

qt_add_executable(WSCreator ${UI} ${CODE} ${QRC})

if(NOT TARGET libws)
    add_subdirectory(../classes libws_build/)
endif()
target_link_libraries(WSCreator PUBLIC libws)

set(QTPROPERTYBROWSER ../../lib/include/qtpropertybrowser/)
include(${QTPROPERTYBROWSER}/src/include.cmake)
include(${QTPROPERTYBROWSER}/pathedit-ext/include.cmake)
BUNDLE_QTPROPERTYBROWSER(WSCreator ${QTPROPERTYBROWSER}/src)
BUNDLE_PATHEDIT_EXT(WSCreator ${QTPROPERTYBROWSER}/pathedit-ext)

target_compile_definitions(WSCreator PUBLIC __WSC_NAME__=\"${PROJECT_NAME}\")
target_compile_definitions(WSCreator PUBLIC __WSC_VERSION__=\"${PROJECT_VERSION}\")

target_include_directories(WSCreator PUBLIC ../classes/)

target_include_directories(WSCreator PUBLIC ${PROJECT_BINARY_DIR})
