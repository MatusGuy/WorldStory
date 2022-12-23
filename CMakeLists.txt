cmake_minimum_required(VERSION 3.16)
project(
    WorldStory
    LANGUAGES CXX
    VERSION 0.0.0.0
    DESCRIPTION "World Story game"
    HOMEPAGE_URL "https://github.com/MatusGuy/WorldStory"
)

#[[ Windows prepare resources
if(WIN32)
    set(PROJECT_COMPANY "MatusGuy")
    set(PROJECT_COPYRIGHT "© 2022 MatusGuy")
    set(PROJECT_PRODUCT "WorldStory")
    set(PROJECT_DISPLAYNAME "World Story")
    set(PROJECT_ORIGINAL_FILENAME "WorldStory.exe")
    set(PROJECT_INTERNALNAME "WS")
endif()
]]

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets)

# Glob & prepare files
file(GLOB_RECURSE SOURCES   src/*.cpp)
file(GLOB_RECURSE HEADERS   src/*.h)
file(GLOB_RECURSE LIBS_SRC  lib/include/*)

# Join sources with headers
set(CODE ${SOURCES} ${HEADERS} ${LIBS_SRC})

if(MSVC)
    file(GLOB UI ui_*.h)
    list(APPEND CODE ${UI})
endif()

file(GLOB_RECURSE FORMS     src/*.ui)
file(GLOB_RECURSE RESOURCES src/*.qrc) # Qt resource system

# Get & remove unneeded files
file(GLOB_RECURSE TO_REM
    # auto generated
    debug/*
    release/*
    out/*
    #./*.h
)
list(REMOVE_ITEM CODE ${TO_REM})

# Add Qt forms
qt_wrap_ui(SOURCES FORMS)

# Add Qt resources
foreach(RC ${RESOURCES})
    qt_add_resources(RESOURCES ${RC})
endforeach()

# Add code to the executable
qt_add_executable(WorldStory ${CODE} ${FORMS} ${RESOURCES})

set_target_properties(WorldStory PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

# Add Windows executable metadata
if (WIN32)
    target_sources(WorldStory PUBLIC WorldStory_resource.rc)
endif()

# Defines
add_definitions(-D__NAME__=\"${PROJECT_NAME}\")
add_definitions(-D__VERSION__=\"${PROJECT_VERSION}\")

target_link_libraries(WorldStory PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::OpenGLWidgets
)

# Give Creator access to game headers
target_include_directories(WorldStory PUBLIC src/classes/)
target_include_directories(WorldStory PUBLIC lib/include/)
if (MSVC)
    target_include_directories(WorldStory PUBLIC ./)
endif()
