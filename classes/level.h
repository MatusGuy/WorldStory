#ifndef LEVEL_H
#define LEVEL_H

#include <QXmlStreamReader>
#include <QFile>
#include <QPixmap>

#include <QtDebug>

#include "gridscene.h"
#include "tilefield.h"

namespace WS {

    namespace Graphics {
        typedef QList<WS::Graphics::Tile*> TileList;
    }

    namespace Levels {

        struct Level {
            ~Level() {
                for (WS::Graphics::Tile* tile : content) {
                    delete tile;
                }
            }

            QString name;
            WS::Graphics::TileList content;

            WS::Graphics::GridScene* grid = nullptr;
        };

        Level* loadLevel(QFile* levelFile);

    }

}

#endif // LEVEL_H
