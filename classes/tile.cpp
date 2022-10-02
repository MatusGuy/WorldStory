#include "tile.h"

using namespace WS::Graphics;

Tile::Tile(GridScene* g): QGraphicsPixmapItem() {
    if (g != nullptr) {
        grid = g;

        grid->tiles.append(this);
        grid->addItem(this);
    }
}

QRectF Tile::boundingRect() const {
    return QRectF(0,0,grid->pointSpacing,grid->pointSpacing);
}

#pragma warning(push)
#pragma warning(disable : 4100) // unreferenced parameter
void Tile::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    QRectF geo = boundingRect();
    geo.setTopLeft(pos());

    painter->drawPixmap(geo.toRect(), pixmap());
}
#pragma warning(pop)
