#ifndef LEVEL_H
#define LEVEL_H

#include <QXmlStreamReader>
#include <QFile>
#include <QStringList>

#include <QtDebug>

namespace WS {

    namespace Graphics {
        class Tile;

        typedef QList<WS::Graphics::Tile*> TileList;
    }

    namespace Levels {

        struct Level {
            QString name;
            WS::Graphics::TileList content;
        };

        Level loadLevel(QFile* levelFile);

    }

}

#include "classes/gridscene.h"

#endif // LEVEL_H
