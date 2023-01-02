#ifndef EDITORSCENE_H
#define EDITORSCENE_H

#include <QGraphicsSceneEvent>
#include <QMenu>
#include <QApplication>
#include <QDrag>
#include <QMimeData>

#include <gridscene.h>

#include "cursor.h"

namespace WS::Creator {

class Viewport;
class SceneGridOverlay;
class EditorScene : public WS::Graphics::GridScene {
    Q_OBJECT

    public:
        EditorScene(QObject *parent = nullptr);
        ~EditorScene();

        void setLevel(WS::Levels::Level* lvl);

        Cursor cursor;
        SceneGridOverlay* gridOverlay = nullptr;
        Viewport* viewport = nullptr;

        QMenu tileMenu;

        signals:
            void tileDragFinished(Tile* tile);

    protected:
        void keyPressEvent(QKeyEvent* event) {Q_UNUSED(event)}

        void mousePressEvent(QGraphicsSceneMouseEvent* event);
        void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);

        void dragEnterEvent(QGraphicsSceneDragDropEvent* event) {};
        void dragMoveEvent(QGraphicsSceneDragDropEvent* event) {};
        void dropEvent(QGraphicsSceneDragDropEvent* event);

        void drawAllTiles();

        protected slots:
            void deleteTile(Tile *tile);

    private:

        private slots:
            void attributeChangeCallback(Tile* tile);
};

}

#include "viewport.h"
#include "scenegridoverlay.h"

#endif // EDITORSCENE_H
