QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES   += $$files(*.cpp, true)
HEADERS   += $$files(*.h,   true)
FORMS     += $$files(*.ui,  true)
RESOURCES += $$files(*.qrc, true)

SOURCES -= classes/tilefield.cpp
HEADERS -= classes/tilefield.h

VERSION = 0.0.0.0
QMAKE_TARGET = WorldStory
QMAKE_TARGET_COMPANY = MatusGuy
QMAKE_TARGET_DESCRIPTION = $$quote(World Story)
QMAKE_TARGET_COPYRIGHT = $$quote(© 2022 MatusGuy)
QMAKE_TARGET_PRODUCT = $$quote(World Story)
QMAKE_TARGET_ORIGINAL_FILENAME = WorldStory.exe
QMAKE_TARGET_INTERNALNAME = WS

DEFINES += __VERSION__=$$quote(\\\"$${VERSION}\\\")
DEFINES += __NAME__=$$quote(\\\"$${QMAKE_TARGET}\\\")

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
