#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QPoint>

#include "scene.h"
#include "level.h"

namespace WS {

namespace Levels { struct Level; }

namespace Graphics {
    class Tile;
    class Grid;

    typedef QList<WS::Graphics::Tile*> TileList;
    //typedef QList<TileList> Grid;

    class GridScene : public WS::Core::Scene {
            Q_OBJECT

            Q_PROPERTY(int tileSize MEMBER tileSize)

        public:
            explicit GridScene(QObject* parent = nullptr);
            ~GridScene();

            QPoint getPointFromGrid(QPoint gpos);

            QPoint getGridPosFrom(QPoint pos);

            /**
             * @brief Spacing between each point in the grid
             * Applies to both coordinates
             * Aka. tile size
             */
            int tileSize = 25;

            QPoint cameraPos;
            QPoint camGridPos();
            QPoint camBottomRight();
            QPoint camGridOffset();

            Grid* world;

            void setLevel(WS::Levels::Level* lvl);

            WS::Levels::Level* level = nullptr;

            void addItem(QGraphicsItem* item);
            void addTile(Tile* tile);

        protected:
            void keyPressEvent(QKeyEvent* event);
            virtual void drawAllTiles();

        protected slots:
            void draw();

        private:
            QPoint oldCamPos;
    };

}  // namespace Graphics

}  // namespace WS

#include "grid.h"

#endif  // GRIDSCENE_H
