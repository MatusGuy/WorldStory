#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <typeinfo>

#include "levelelement.h"

namespace WS {

namespace Graphics {

    enum SceneSide {
        None = 0,

        Left = 1,
        Right = 2,
        Up = 4,
        Down = 8,
    };

    class Tile : public QGraphicsPixmapItem, WS::Levels::ILevelElement {
        public:
            Tile();

            QRectF boundingRect() const;
            void paint(
                QPainter* painter,
                const QStyleOptionGraphicsItem* option,
                QWidget* widget
            );

            int& size = NULL;

            SceneSide isOffscreenFrom();

            QPoint gridPos;

        protected:
            virtual void setupAttributes();

        // ILevelElement interface
        public:
            virtual const QString internalName() {return "tile";}
            virtual void setAttribute(QString name, QString value);
            virtual QVariant getAttribute(QString name);
    };

}  // namespace Graphics

}  // namespace WS

#endif  // TILE_H
