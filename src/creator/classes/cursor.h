#ifndef CURSOR_H
#define CURSOR_H

#include <tile.h>

namespace WS::Creator {

using WS::Graphics::Tile;

class Cursor : public Tile {
        Q_OBJECT

        Q_PROPERTY(
            Tile* selecting
            READ selecting
            WRITE select
            MEMBER _selecting
            NOTIFY selectionChanged
        );

    public:
        Cursor();

        Tile* selecting();
        void select(Tile* tile);
        void unselect();

        void paint(
            QPainter* painter,
            const QStyleOptionGraphicsItem* option,
            QWidget* widget
        );

    signals:
        void selectionChanged();

    protected:
        Tile* _selecting = nullptr;

        QPen highlightPen;
        QPen cornerPen;
};

}

#endif // CURSOR_H
