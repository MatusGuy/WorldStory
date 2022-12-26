#ifndef TILE_H
#define TILE_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QUrl>
#include <QPainter>

#include "levelelement.h"

namespace WS {

namespace Graphics {

    class Grid;

    enum SceneSide {
        None = 0,

        Left = 1,
        Right = 2,
        Up = 4,
        Down = 8,
    };

    class Tile : public WS::Levels::ILevelElement, public QGraphicsItem {
        public:
            Tile();

            QRectF boundingRect() const;
            void paint(
                QPainter* painter,
                const QStyleOptionGraphicsItem* option,
                QWidget* widget
            );

            SceneSide isOffscreenFrom();

            inline void setPixmap(QUrl pUrl) {
                pixUrl = pUrl;
                pix = QPixmap(pUrl.path());
            };
            inline QPixmap& pixmap() { return pix; };

            int size;

            QPoint gridPos;
            Grid* world = nullptr;

        private:
            QPixmap pix;
            QUrl pixUrl;

        protected:
            void setupAttributes();

            // ILevelElement interface
        public:
            virtual const QString internalName() { return "tile"; }
            virtual void setAttribute(QString name, QString value);
            virtual QVariant getAttribute(QString name);
    };

}  // namespace Graphics

}  // namespace WS

#include "grid.h"

#endif  // TILE_H
