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
    cursor.gridPos = getGridPosFrom(event->scenePos().toPoint());
    Tile* selected = world->get(cursor.gridPos);
    if (event->button() == Qt::LeftButton) {
        cursor.select(selected);

        if (selected != nullptr) {
            QDrag* drag = new QDrag(event->widget());
            QMimeData* mime = new QMimeData;
            Tile* selecting = cursor.selecting();
            mime->setData("text/plain", (QString("%1,%2").arg(selecting->gridPos.x()).arg(selecting->gridPos.y())).toUtf8());
            drag->setMimeData(mime);
            drag->exec(Qt::MoveAction);
        }
    } else if (event->button() == Qt::MiddleButton) {
        world->remove(selected);
    } else {
        event->ignore();
        return;
    }

    WS::Graphics::GridScene::mousePressEvent(event);
}

void EditorScene::contextMenuEvent(QGraphicsSceneContextMenuEvent* event) {
    cursor.gridPos = getGridPosFrom(event->scenePos().toPoint());
   
    cursor.select(world->get(cursor.gridPos));
    tileMenu.exec(event->screenPos());
    cursor.unselect();

    WS::Graphics::GridScene::contextMenuEvent(event);
}

void EditorScene::dropEvent(QGraphicsSceneDragDropEvent* event) {
    if (event->mimeData()->hasFormat("text/plain")) {
        QStringList pos = QString(event->mimeData()->data("text/plain").data()).split(',');
        int x = pos[0].toInt();
        int y = pos[1].toInt();

        Tile* selected = world->get(x,y);
        
        selected->setAttributeFromVariant("pos", getGridPosFrom(event->scenePos().toPoint()));

        emit tileDragFinished(selected);
    } else {
        event->ignore();
    }
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
