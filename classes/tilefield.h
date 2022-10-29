#ifndef TILEFIELD_H
#define TILEFIELD_H

#include <QPoint>
#include <QSize>

#include "classes/tile.h"

namespace WS::Graphics {

class QT_DEPRECATED TileField : public WS::Graphics::Tile {
    public:
        TileField(Levels::Level* lvl);

        QRectF boundingRect() const;

        QSize size;

        void paint(
            QPainter* painter,
            const QStyleOptionGraphicsItem* option,
            QWidget* widget
        );
};

}  // namespace WS::Graphics

#endif  // TILEFIELD_H
