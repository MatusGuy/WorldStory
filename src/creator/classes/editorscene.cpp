#include "editorscene.h"

using namespace WS::Creator;
using namespace WS::Graphics;

EditorScene::EditorScene(QObject *parent) : GridScene{parent} {
    addTile(&cursor);
    tileMenu.setFocusPolicy(Qt::NoFocus);
}

void EditorScene::setLevel(Levels::Level *lvl) {
    GridScene::setLevel(lvl);

    connect(
        world, &Grid::tileRemoved,
        this, &EditorScene::deleteTile
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
    cursor.gridPos = getGridPosFromEvent(event);
    Tile* selected = world->get(cursor.gridPos);
    if (event->button() == Qt::LeftButton) {
        cursor.select(selected);
        cursor.isDragging = true;
    } else if (event->button() == Qt::MiddleButton) {
        world->remove(selected);
    } else {
        event->ignore();
        return;
    }

    WS::Graphics::GridScene::mousePressEvent(event);
}

void EditorScene::contextMenuEvent(QGraphicsSceneContextMenuEvent* event) {
    //cursor.gridPos = getGridPosFromEvent(event);
   
    //cursor.select(world->get(cursor.gridPos));
    tileMenu.exec(event->screenPos());
    //cursor.unselect();

    WS::Graphics::GridScene::contextMenuEvent(event);
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

template<typename QGSEvent>
QPoint EditorScene::getGridPosFromEvent(QGSEvent *event) {
    QPoint curPos = cameraPos + event->scenePos().toPoint();
    return QPoint(curPos.x() / tileSize, curPos.y() / tileSize);
}

void EditorScene::deleteTile(Tile *tile) {
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
