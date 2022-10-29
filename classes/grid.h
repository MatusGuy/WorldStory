#ifndef GRID_H
#define GRID_H

#include <QObject>

#include "tile.h"

namespace WS::Graphics {

class Grid : public QObject {
        Q_OBJECT

    public:
        explicit Grid(QObject *parent = nullptr);

        void place(QPoint pos, Tile tile);
        void place(int x, int y, Tile tile);

        Tile get(QPoint pos);
        Tile get(int x, int y);

    signals:

    private:
        QList<QList<Tile>> content;
};

}  //namespace WS::Graphics

#endif  // GRID_H
