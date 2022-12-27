#ifndef EDITORSCENE_H
#define EDITORSCENE_H

#include <QGraphicsSceneEvent>
#include <QMenu>
#include <QApplication>

#include <gridscene.h>

#include "cursor.h"

namespace WS::Creator {

class EditorScene : public WS::Graphics::GridScene {
    Q_OBJECT

    public:
        explicit EditorScene(QObject *parent = nullptr);

        void setLevel(WS::Levels::Level* lvl);

        Cursor cursor;

        QMenu tileMenu;

    protected:
        void keyPressEvent(QKeyEvent* event) {Q_UNUSED(event)}

        void mousePressEvent(QGraphicsSceneMouseEvent* event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
        void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);

        void drawAllTiles();

        protected slots:
            void deleteTile(Tile *tile);

    private:

        private slots:
            void attributeChangeCallback(Tile* tile);
};

}

#endif // EDITORSCENE_H
