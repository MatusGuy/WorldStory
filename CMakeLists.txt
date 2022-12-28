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
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets)

# Glob & prepare files
file(GLOB_RECURSE SOURCES   src/*.cpp)
file(GLOB_RECURSE HEADERS   src/*.h)

# Join sources with headers
set(CODE ${SOURCES} ${HEADERS})

file(GLOB_RECURSE FORMS     src/*.ui)
file(GLOB_RECURSE RESOURCES src/*.qrc) # Qt resource system

# Compile forms
qt_wrap_ui(UI ${FORMS})
message("${UI} ${PROJECT_BINARY_DIR}")

# Get & remove unneeded files
file(GLOB_RECURSE TO_REM
    # auto generated
    debug/*
    release/*
    out/*
    #./*.h
)
list(REMOVE_ITEM CODE ${TO_REM})

# Add Qt resources
foreach(QRC ${RESOURCES})
    qt_add_resources(RCC ${QRC})
endforeach()

# Add code to the executable
qt_add_executable(WorldStory ${CODE} ${UI} ${FORMS} ${RESOURCES} ${RCC})

# Prepare for deployment
set_target_properties(WorldStory PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

# Add Windows executable metadata
set(RC "WorldStory_resource.rc")
if (WIN32 AND EXISTS ${RC})
    target_sources(WorldStory PUBLIC ${RC})
endif()

# Defines
add_definitions(-D__WS_NAME__=\"${PROJECT_NAME}\")
add_definitions(-D__WS_VERSION__=\"${PROJECT_VERSION}\")

# Libraries
set(QTPROPERTYBROWSER lib/include/qtpropertybrowser/)
include(${QTPROPERTYBROWSER}/src/include.cmake)
include(${QTPROPERTYBROWSER}/pathedit-ext/include.cmake)
BUNDLE_QTPROPERTYBROWSER(WorldStory ${QTPROPERTYBROWSER}/src)
BUNDLE_PATHEDIT_EXT(WorldStory ${QTPROPERTYBROWSER}/pathedit-ext)

# Qt
target_link_libraries(WorldStory PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::OpenGLWidgets
)

# Give Creator access to game headers
target_include_directories(WorldStory PUBLIC src/classes/)

# Add compiled forms and other things to includepath
target_include_directories(WorldStory PUBLIC ${PROJECT_BINARY_DIR})
