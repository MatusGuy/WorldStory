#include "gridscene.h"

using namespace WS::Graphics;

GridScene::GridScene(QObject* parent) : WS::Core::Scene(parent) {
    assert(pointSpacing >= 0);
}

QPoint GridScene::getPoint(int x, int y) {
    return QPoint(x * pointSpacing, y * pointSpacing);
}

void GridScene::draw() {
    assert(level != nullptr);

    if (offset == oldoff) return;

    QPoint bottomRight = sceneRect().bottomRight().toPoint() + offset;

    toDraw = (TileList)crop2DListFromRanges<Tile*>(
        level->content,
        offset.x(),
        offset.y(),
        bottomRight.x(),
        bottomRight.y()
    );

    for (Tile* tile : toDraw) {
        //tile->setPos(getPoint(tile->initPos.x(), tile->initPos.y()) - offset);
        tile->update();
    }

    oldoff = offset;
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
            offset.rx() -= 5;
            break;

        case Qt::Key_D:
            offset.rx() += 5;
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
        world[tile->gridPos.x()][tile->gridPos.y()] = tile;
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
