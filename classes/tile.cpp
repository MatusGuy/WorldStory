#include "tile.h"

using namespace WS::Graphics;
using WS::Levels::Level;

Tile::Tile(Level* lvl): QGraphicsPixmapItem() {
    level = lvl;

    level->content.append(this);

    if (level->grid != nullptr) level->grid->addItem(this);
}

QRectF Tile::boundingRect() const {
    return QRectF(0,0,level->grid->pointSpacing+x(),level->grid->pointSpacing+y());
}

void Tile::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);

    QRectF geo = boundingRect();
    geo.setTopLeft(pos());

    painter->setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
    painter->drawPixmap(geo.toRect(), pixmap());



    //QGraphicsPixmapItem::paint(painter, option, widget);
}
