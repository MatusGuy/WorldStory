#include "editorscene.h"

using namespace WS::Creator;
using namespace WS::Graphics;

EditorScene::EditorScene(QObject *parent) : GridScene{parent} {
    addTile(&cursor);
}

void EditorScene::setLevel(Levels::Level *lvl) {
    GridScene::setLevel(lvl);

    connect(
        world, &Grid::tileRemoved,
        this, &EditorScene::deleteTileCallback
    );

    for (const QMap<int, Tile*> column : world->map()) {
        for (Tile* tile : column) {
            connect(
                tile, &Tile::attributeChanged,
                [this, tile](QString, QVariant, QVariant) {
                    attributeChangeCallback(tile);
                }
            );
        }
    }

    connect(
        world, &Grid::tileAdded,
        [this](Tile* tile) {
            connect(
                tile, &Tile::attributeChanged,
                [this, tile](QString, QVariant, QVariant) {
                    attributeChangeCallback(tile);
                }
            );
        }
    );
}

void EditorScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QPoint curPos = cameraPos + event->scenePos().toPoint();
    //cursor.setPos(qFloor<int>(curPos.x() / tileSize)*tileSize, qFloor<int>(curPos.y() / tileSize)*tileSize);
    cursor.gridPos.setX(curPos.x() / tileSize);
    cursor.gridPos.setY(curPos.y() / tileSize);
    if (event->button() == Qt::LeftButton) {
        cursor.select(world->get(cursor.gridPos));
    } else if (event->button() == Qt::RightButton) {
        if (tileMenu.isVisible()) tileMenu.close();

        cursor.select(world->get(cursor.gridPos));
        if (cursor.selecting() == nullptr) return;

        tileMenu.exec(event->screenPos());
        cursor.unselect();
    }

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

void EditorScene::deleteTileCallback(Tile *tile) {
    tile->hide();
    cursor.unselect();
    cursor.gridPos *= 0; // lmfao
    removeItem(tile);
    drawAllTiles();
    delete tile;
}

void EditorScene::attributeChangeCallback(Tile* tile) {
    if (tile == cursor.selecting()) {
        cursor.gridPos = tile->gridPos;
    }
    drawAllTiles();
}