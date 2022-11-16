#ifndef GRID_H
#define GRID_H

#include <QObject>
#include <QPoint>

#include "tile.h"

#include <iterator>
#include <cstddef>

namespace WS::Graphics {

/**
 * @brief The Grid class stores the content in a level.
 */
class Grid : public QObject {
        Q_OBJECT

    public:
        explicit Grid(QObject *parent = nullptr);
        ~Grid();

        void place(int x, int y, Tile* tile);
        void place(QPoint& pos, Tile* tile);

        Tile* get(int x, int y);
        Tile* get(QPoint& pos);

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

    private:
        QMap<int, QMap<int, Tile*>> content;
};

}  //namespace WS::Graphics

#endif  // GRID_H
