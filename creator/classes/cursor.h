#ifndef CURSOR_H
#define CURSOR_H

#include <classes/tile.h>

namespace WS::Creator {

using WS::Graphics::Tile;

class Cursor : public Tile {

    public:
        Cursor();

        Tile* selecting = nullptr;

        void select(Tile* tile);
        void unselect();

        void paint(
            QPainter* painter,
            const QStyleOptionGraphicsItem* option,
            QWidget* widget
        );

    protected:
        QPen highlightPen;
        QPen cornerPen;
};

}

#endif // CURSOR_H
