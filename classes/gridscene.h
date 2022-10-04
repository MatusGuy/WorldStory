#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QGraphicsScene>
#include <QPoint>
#include <QList>

#include "classes/scene.h"


namespace WS {

namespace Levels { struct Level; }

namespace Graphics {

class Tile;

class GridScene : public WS::Core::Scene {
    Q_OBJECT

    Q_PROPERTY(int pointSpacing MEMBER pointSpacing)

    public:
        explicit GridScene(QObject* parent = nullptr);

        /**
         * @brief Get QPoint% from position on the grid
         * @param x horizontal position of the wanted grid space
         * @param y vertical position of the wanted grid space
         * @return location relative to game display
         */
        QPoint getPoint(int x, int y);

        /**
         * @brief Spacing between each point in the grid
         * Applies to both coordinates
         */
        int pointSpacing = 25;

        void setLevel(WS::Levels::Level* lvl);

        WS::Levels::Level* level = nullptr;

        void addItem(QGraphicsItem *item);

        signals:



    protected:

        protected slots:
            void draw();
};

}

}

#include "classes/level.h"
#include "classes/tile.h"

#endif // GRIDSCENE_H
