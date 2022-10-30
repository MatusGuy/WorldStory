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

        void place(int x, int y, Tile* tile);
        Tile* get(int x, int y);

        /**
         * @brief Get row at @c pos
         * @param pos row position
         * @return Row
         */
        QMap<int, Tile*> row(int pos);

        /**
         * @brief Get column at @c pos
         * @param pos column position
         * @return Column
         */
        QMap<int, Tile*>& column(int pos);

        /**
         * @brief Get all tiles inside @c zone
         * @param zone Tile range
         * @return Tiles within @c zone
         */
        QList<Tile*> capture(const QPoint& topLeft, const QPoint& bottomRight);


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
