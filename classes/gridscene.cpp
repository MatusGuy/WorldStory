#include "gridscene.h"

using namespace WS::Graphics;

GridScene::GridScene(QObject* parent) : WS::Core::Scene(parent) {
    world = nullptr;
}

GridScene::~GridScene() {
    //delete world;
}

QPoint GridScene::getPoint(int x, int y) {
    return QPoint(x * tileSize, y * tileSize);
}

void GridScene::draw() {
    assert(level != nullptr);

    if (cameraPos == oldCamPos && loopStarted) return;

    //QPoint bottomRight = sceneRect().bottomRight().toPoint() + cameraPos;

    //qDebug() << cameraPos << bottomRight;

    QPoint gridCamPos;
    gridCamPos.setX(cameraPos.x()/tileSize);
    gridCamPos.setY(cameraPos.y()/tileSize);
    //= cameraPos/tileSize;
    QPoint camSize = cameraPos + sceneRect().bottomRight().toPoint();
    QPoint offset(cameraPos.x()%tileSize, cameraPos.y()%tileSize);

    //qDebug() << "camera pos:" << cameraPos;
    //qDebug() << "ri rj:" << gridCamPos;
    //int i=0;
    for (Tile* tile : world->capture(gridCamPos-QPoint(1,1), (camSize/tileSize)+QPoint(1,1))) {
        //QPoint pos = getPoint(tile->gridPos.x(),tile->gridPos.y())-cameraPos*tileSize;
        QPoint pos((tile->gridPos - gridCamPos) * tileSize - offset);
        //qDebug() << pos;
        tile->setPos(pos);
        tile->update();
        //i++;
    }
    //qDebug() << "screen tiles:" << i;

    oldCamPos = cameraPos;
}

void GridScene::addItem(QGraphicsItem* item) {
    WS::Core::Scene::addItem(item);
    //qDebug() << "old" << item->pos() << item->boundingRect().bottomRight();
    //item->setPos(getPoint(item->x(), item->y()));
    //qDebug() << "new" << item->pos() << item->boundingRect().bottomRight();
}

void GridScene::addTile(Tile* tile) {
    addItem(tile);
    tile->setPos(-tileSize, -tileSize);
    tile->size = tileSize;
}

void GridScene::keyPressEvent(QKeyEvent* event) {
    //qDebug() << "press!!!!!";
    switch (event->key()) {
        case Qt::Key_A:
            cameraPos.rx() -= tileSize/5;
            break;

        case Qt::Key_D:
            cameraPos.rx() += tileSize/5;
            break;

        case Qt::Key_W:
            cameraPos.ry() -= tileSize/5;
            break;

        case Qt::Key_S:
            cameraPos.ry() += tileSize/5;
            break;

        default:
            break;
    }
}

void GridScene::setLevel(WS::Levels::Level* lvl) {
    /*
    if (world->parent() != nullptr)
        for (const QMap<int, Tile*>& column : world->map())
            for (Tile* tile : column) {
                removeItem(tile);
                tile->size = nullptr;
            }
    */

    level = lvl;

    world = &level->content;
    world->setParent(this);

    for (const QMap<int, Tile*>& column : world->map())
        for (Tile* tile : column) {
            addItem(tile);
            tile->setPos(-tileSize,-tileSize);
            tile->size = tileSize;
        }

    draw();
}

template <typename T>
QList<T> GridScene::cropListFromRange(QList<T>* list, int a, int b) {
    QList<T> out;
    for (int i = a; i < b; i++) {
        out.append(list[i]);
    }
    return out;
}

template <typename T>
QList<T> GridScene::crop2DListFromRanges(
    QList<QList<T>>* list2d,
    int ax,
    int bx,
    int ay,
    int by
) {
    QList<T> out;
    for (int ix = ax; ix < bx; ix++) {
        out.append(cropListFromRange<T>(&list2d[ix], ay, by));
    }
}
