#include "gridscene.h"

using namespace WS::Graphics;

GridScene::GridScene(QObject *parent): WS::Core::Scene(parent) {
    assert(pointSpacing>=0);

}

QPoint GridScene::getPoint(int x, int y) {
    return QPoint(x*pointSpacing, y*pointSpacing);
}

void GridScene::draw() {
    for (Tile* tile : tiles) {
        tile->update();
    }
}
