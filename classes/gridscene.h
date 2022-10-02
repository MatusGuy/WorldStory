#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QGraphicsScene>
#include <QPoint>
#include <QList>

#include "classes/scene.h"

namespace WS {

namespace Graphics {

class Tile;

class GridScene : public WS::Core::Scene {
    Q_OBJECT

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
        int pointSpacing = 10;

        QList<WS::Graphics::Tile*> tiles;

        signals:



    protected:

        protected slots:
            void draw();
};

}

}

#include "classes/tile.h"

#endif // GRIDSCENE_H
