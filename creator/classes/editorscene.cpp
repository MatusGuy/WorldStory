#include "editorscene.h"

using namespace WS::Creator;
using WS::Graphics::Tile;

EditorScene::EditorScene(QObject *parent) : WS::Graphics::GridScene{parent} {
    addTile(&cursor);
}

void EditorScene::setLevel(Levels::Level *lvl) {
    WS::Graphics::GridScene::setLevel(lvl);

    connect(
        world, &WS::Graphics::Grid::tileChanged, this, &EditorScene::deleteTileCallback
    );
}

void EditorScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QPoint curPos = cameraPos + event->scenePos().toPoint();
    //cursor.setPos(qFloor<int>(curPos.x() / tileSize)*tileSize, qFloor<int>(curPos.y() / tileSize)*tileSize);
    cursor.gridPos.setX(curPos.x() / tileSize);
    cursor.gridPos.setY(curPos.y() / tileSize);

    cursor.select(world->get(cursor.gridPos));

    qDebug() << curPos << cursor.gridPos;
    WS::Graphics::GridScene::mousePressEvent(event);
}

void EditorScene::drawAllTiles() {
    //QPoint bottomRight = sceneRect().bottomRight().toPoint() + cameraPos;

    //qDebug() << cameraPos << bottomRight;

    QPoint gridCamPos = camGridPos();
    bool cursorIsSelecting = false;

    //qDebug() << "camera pos:" << cameraPos;
    //qDebug() << "ri rj:" << gridCamPos;
    //int i=0;
    for (Tile *tile : world->capture(gridCamPos - QPoint(1, 1), (camBottomRight() / tileSize) + QPoint(1, 1))) {
        //QPoint pos = getPoint(tile->gridPos.x(),tile->gridPos.y())-cameraPos*tileSize;
        QPoint pos((tile->gridPos - gridCamPos) * tileSize - camGridOffset());
        //qDebug() << pos;
        tile->setPos(pos);
        tile->update();

        if ((tile->gridPos == cursor.gridPos) && !cursorIsSelecting) {
            cursorIsSelecting = true;
            cursor.select(tile);
        }

        //i++;
    }

    if (!cursorIsSelecting) cursor.unselect();

    //qDebug() << "screen tiles:" << i;
}

void EditorScene::deleteTileCallback(Tile *oldTile, Tile *newTile) {
    qDebug() << "delete";
    if (newTile == nullptr) {
        oldTile->hide();
        cursor.unselect();
        cursor.gridPos *= 0; // lmfao
        removeItem(oldTile);
        drawAllTiles();
        delete oldTile;
    }
}
