#ifndef EDITORSCENE_H
#define EDITORSCENE_H

#include <QGraphicsSceneMouseEvent>

#include <classes/gridscene.h>

#include "cursor.h"

namespace WS::Creator {

class EditorScene : public WS::Graphics::GridScene {
    Q_OBJECT

    public:
        explicit EditorScene(QObject *parent = nullptr);

        void setLevel(WS::Levels::Level* lvl);

        Cursor cursor;

    protected:
        void keyPressEvent(QKeyEvent* event) {Q_UNUSED(event)}

        void mousePressEvent(QGraphicsSceneMouseEvent* event);

        void drawAllTiles();

        protected slots:
        void deleteTileCallback(Tile *oldTile, Tile *newTile);
};

}

#endif // EDITORSCENE_H
