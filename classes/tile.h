#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>
#include <QPainter>

#include "classes/gridscene.h"

namespace WS {

namespace Levels { struct Level; }

namespace Graphics {

class Tile : public QGraphicsPixmapItem {
    public:
        Tile(WS::Levels::Level* lvl);

        QRectF boundingRect() const;
        void paint(
            QPainter* painter,
            const QStyleOptionGraphicsItem* option,
            QWidget* widget
        );

    private:
        WS::Levels::Level* level = nullptr;
};

}

}

#endif // TILE_H
