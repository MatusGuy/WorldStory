#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <typeinfo>

namespace WS {

// clang-format off
namespace Levels { struct Level; }
// clang-format on

namespace Graphics {

    enum SceneSide {
        None = 0,

        Left = 1,
        Right = 2,
        Up = 4,
        Down = 8,
    };

    class Tile : public QGraphicsPixmapItem {
        public:
            Tile(WS::Levels::Level* lvl);

            QRectF boundingRect() const;
            void paint(
                QPainter* painter,
                const QStyleOptionGraphicsItem* option,
                QWidget* widget
            );

            WS::Graphics::SceneSide isOffscreenFrom();

            QPoint gridPos;

            QPoint initPos;

        protected:
            WS::Levels::Level* level = nullptr;
    };

}  // namespace Graphics

}  // namespace WS

#include "level.h"

#endif  // TILE_H
