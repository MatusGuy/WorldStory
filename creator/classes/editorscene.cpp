#include "editorscene.h"

using namespace WS::Creator;
using WS::Graphics::Tile;

EditorScene::EditorScene(QObject *parent): WS::Graphics::GridScene{parent} {
    addTile(&cursor);
    cursor.setZValue(2);
}

void EditorScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QPoint curPos = event->scenePos().toPoint();
    //cursor.setPos(qFloor<int>(curPos.x() / tileSize)*tileSize, qFloor<int>(curPos.y() / tileSize)*tileSize);
    cursor.gridPos = curPos / tileSize;
    qDebug() << curPos << cursor.pos();
    WS::Graphics::GridScene::mousePressEvent(event);
}

void EditorScene::drawAllTiles() {
    //QPoint bottomRight = sceneRect().bottomRight().toPoint() + cameraPos;

    //qDebug() << cameraPos << bottomRight;

    QPoint gridCamPos = camGridPos();

    //qDebug() << "camera pos:" << cameraPos;
    //qDebug() << "ri rj:" << gridCamPos;
    //int i=0;
    for (Tile *tile : world->capture(gridCamPos - QPoint(1, 1), (camBottomRight() / tileSize) + QPoint(1, 1))) {
        //QPoint pos = getPoint(tile->gridPos.x(),tile->gridPos.y())-cameraPos*tileSize;
        QPoint pos((tile->gridPos - gridCamPos) * tileSize - camGridOffset());
        //qDebug() << pos;
        tile->setPos(pos);
        tile->update();


        cursor.update();

        //i++;
    }
    //qDebug() << "screen tiles:" << i;
}

