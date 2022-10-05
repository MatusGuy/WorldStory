#include "gridscene.h"

using namespace WS::Graphics;

GridScene::GridScene(QObject *parent): WS::Core::Scene(parent) {

    assert(pointSpacing>=0);

}

QPoint GridScene::getPoint(int x, int y) {
    return QPoint(x*pointSpacing, y*pointSpacing);
}

void GridScene::draw() {
    assert(level!=nullptr);

    for (Tile* tile : level->content) {
        //qDebug() << tile << tile->parentItem();
        tile->update();
    }
}

void GridScene::addItem(QGraphicsItem* item) {
    WS::Core::Scene::addItem(item);
    //qDebug() << "old" << item->pos() << item->boundingRect().bottomRight();
    item->setPos(getPoint(item->x(), item->y()));
    qDebug() << "new" << item->pos() << item->boundingRect().bottomRight();
}

void GridScene::setLevel(WS::Levels::Level* lvl) {
    if (lvl->grid != nullptr) {

        for (Tile* tile : lvl->content) lvl->grid->removeItem(tile);

        lvl->grid->level = nullptr;
    }

    level = lvl;
    level->grid = this;
    for (Tile* tile : level->content) addItem(tile);
}

