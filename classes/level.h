#ifndef LEVEL_H
#define LEVEL_H

#include <QXmlStreamReader>
#include <QFile>
#include <QPixmap>

#include <QtDebug>

#include "grid.h"

#if defined(_MSC_VER)
#define global __declspec(selectany)
#elif defined(__GNUG__)
#define global __attribute__((weak))
#endif

namespace WS::Levels {
    global QXmlStreamReader xmlReader;

    struct Level {

        QString name;
        WS::Graphics::Grid content;
    };

    Level* loadLevel(QFile* levelFile);

}

#endif // LEVEL_H
