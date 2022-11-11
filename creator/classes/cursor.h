#ifndef CURSOR_H
#define CURSOR_H

#include <classes/tile.h>

namespace WS::Creator {

class Cursor : public WS::Graphics::Tile {

    public:
        Cursor();

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
