#ifndef LEVEL_H
#define LEVEL_H

#include <QXmlStreamReader>
#include <QFile>
#include <QPixmap>

#include <QtDebug>

namespace WS {

    namespace Graphics {
        class GridScene;
        class Tile;

        typedef QList<WS::Graphics::Tile*> TileList;
    }

    namespace Levels {

        struct Level {
            QString name;
            WS::Graphics::TileList content;

            WS::Graphics::GridScene* grid = nullptr;
        };

        Level* loadLevel(QFile* levelFile);

    }

}

#include "classes/tile.h"

#endif // LEVEL_H
