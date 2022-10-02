#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>
#include <QPainter>

#include "classes/gridscene.h"

namespace WS {

namespace Graphics {

class Tile : public QGraphicsPixmapItem {
    public:
        Tile(WS::Graphics::GridScene* g = nullptr);

        QRectF boundingRect() const;
        void paint(
            QPainter* painter,
            const QStyleOptionGraphicsItem* option,
            QWidget* widget
        );

    private:
        GridScene* grid;
};

}

}

#endif // TILE_H
