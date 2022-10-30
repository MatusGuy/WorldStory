#include "gridscene.h"

using namespace WS::Graphics;

GridScene::GridScene(QObject* parent) : WS::Core::Scene(parent) {
    //world = new Grid(this);
}

GridScene::~GridScene() {
    //delete world;
}

QPoint GridScene::getPoint(int x, int y) {
    return QPoint(x * tileSize, y * tileSize);
}

void GridScene::draw() {
    assert(level != nullptr);

    if (cameraPos == oldCamPos) return;

    QPoint bottomRight = sceneRect().bottomRight().toPoint() + cameraPos;

    for (Tile* tile : world->capture(cameraPos, bottomRight)) {
        //tile->setPos(getPoint(tile->initPos.x(), tile->initPos.y()) - offset);
        tile->update();
    }

    oldCamPos = cameraPos;
}

void GridScene::addItem(QGraphicsItem* item) {
    WS::Core::Scene::addItem(item);
    //qDebug() << "old" << item->pos() << item->boundingRect().bottomRight();
    //item->setPos(getPoint(item->x(), item->y()));
    //qDebug() << "new" << item->pos() << item->boundingRect().bottomRight();
}

void GridScene::keyPressEvent(QKeyEvent* event) {
    //qDebug() << "press!!!!!";
    switch (event->key()) {
        case Qt::Key_A:
            cameraPos.rx() += 1;
            break;

        case Qt::Key_D:
            cameraPos.rx() -= 1;
            break;

        default:
            break;
    }
}

void GridScene::setLevel(WS::Levels::Level* lvl) {
    if (lvl->grid != nullptr) {
        for (Tile* tile : lvl->content) lvl->grid->removeItem(tile);

        lvl->grid->level = nullptr;
    }

    level = lvl;
    level->grid = this;
    for (Tile* tile : level->content) {
        world->place(tile->gridPos.x(), tile->gridPos.y(), tile);
        addItem(tile);
    }
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
