#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QList>
#include <QPoint>

#include "classes/scene.h"

namespace WS {

// clang-format off
namespace Levels { struct Level; }
// clang-format on

namespace Graphics {

    class Tile;

    typedef QList<WS::Graphics::Tile*> TileList;
    typedef QList<TileList> Grid;

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
             * Aka. tile size
             */
            int pointSpacing = 25;

            QPoint offset;

            Grid world;

            void setLevel(WS::Levels::Level* lvl);

            WS::Levels::Level* level = nullptr;

            void addItem(QGraphicsItem* item);

            template <typename T>
            static QList<T> cropListFromRange(QList<T>* list, int a, int b);

            template <typename T>
            static QList<T> crop2DListFromRanges(
                QList<QList<T>>* list2d,
                int ax,
                int bx,
                int ay,
                int by
            );

        signals:

        protected:
            void keyPressEvent(QKeyEvent* event);

            WS::Graphics::TileList toDraw;

        protected slots:
            void draw();

        private:
            QPoint oldoff;
    };

}  // namespace Graphics

}  // namespace WS

#include "classes/level.h"
#include "classes/tile.h"

#endif  // GRIDSCENE_H
