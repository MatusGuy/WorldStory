#ifndef GRID_H
#define GRID_H

#include <QObject>
#include <QPoint>

#include "tile.h"

namespace WS::Graphics {

/**
 * @brief The Grid class stores the content in a level.
 */
class Grid : public QObject {
        Q_OBJECT

    public:
        explicit Grid(QObject *parent = nullptr);
        ~Grid();

        void place(Tile* tile);

        Tile* get(int x, int y);
        Tile* get(QPoint& pos);

        void remove(Tile* tile);

        void move(Tile* tile, int x, int y);
        void move(Tile* tile, QPoint& pos);

        bool find(Tile* tile);

        void sync(Tile* tile);

        /**
         * @brief Get row at @c pos
         */
        QMap<int, Tile*> row(int pos);

        /**
         * @brief Get column at @c pos
         */
        QMap<int, Tile*>& column(int pos);

        /**
         * @brief Get all tiles from @c topLeft to @c bottomLeft
         */
        QList<Tile*> capture(const QPoint& topLeft, const QPoint& bottomRight);

        const QMap<int, QMap<int, Tile*>>& map();

        /**
         * @brief Deletes grid content when calling deleting grid.
         */
        bool clearOnDestruction = true;

    signals:
        void tileAdded(Tile* tile);
        void tileRemoved(Tile* tile);
        void tileMoved(Tile* tile);

    private:
        QMap<int, QMap<int, Tile*>> content;
};

}  //namespace WS::Graphics

#endif  // GRID_H
