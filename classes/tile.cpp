#include "tile.h"

using namespace WS::Graphics;
using WS::Levels::Level;

Tile::Tile(Level* lvl): QGraphicsPixmapItem() {
    level = lvl;

    level->content.append(this);

    if (level->grid != nullptr) level->grid->addItem(this);
}

QRectF Tile::boundingRect() const {
    return QRectF(
        0,0,
        level->grid->pointSpacing,level->grid->pointSpacing
    );
}

void Tile::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);

    QRectF geo = boundingRect();
    painter->drawPixmap(geo.toRect(), pixmap());
    painter->drawRect(geo);


    //QGraphicsPixmapItem::paint(painter, option, widget);
}
