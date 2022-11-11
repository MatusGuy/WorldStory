#include "editorscene.h"

using namespace WS::Creator;

EditorScene::EditorScene(QObject *parent): WS::Graphics::GridScene{parent} {
    addTile(&cursor);
    cursor.setZValue(2);
}

void EditorScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QPoint curPos = event->scenePos().toPoint();
    cursor.setPos(qFloor<int>(curPos.x() / tileSize)*tileSize, qFloor<int>(curPos.y() / tileSize)*tileSize);
    qDebug() << curPos << cursor.pos();  //QPoint(qFloor<int>(curPos.x() / tileSize), qFloor<int>(curPos.y() / tileSize));
    WS::Graphics::GridScene::mousePressEvent(event);
}

void EditorScene::draw() {
    WS::Graphics::GridScene::draw();
    cursor.update();
}
