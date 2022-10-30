#ifndef LEVEL_H
#define LEVEL_H

#include <QXmlStreamReader>
#include <QFile>
#include <QPixmap>

#include <QtDebug>

#include "grid.h"

namespace WS::Levels {

    struct Level {

        QString name;
        WS::Graphics::Grid content;
    };

    Level* loadLevel(QFile* levelFile);

}

#endif // LEVEL_H
