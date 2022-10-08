#include "tile.h"

using namespace WS::Graphics;
using WS::Levels::Level;

Tile::Tile(Level* lvl): QGraphicsPixmapItem() {
    setCacheMode(CacheMode::DeviceCoordinateCache);

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

    if (!isOffscreenFrom()) return;

    QRectF geo = boundingRect();
    painter->drawPixmap(geo.toRect(), pixmap());

    //QGraphicsPixmapItem::paint(painter, option, widget);
}

SceneSide Tile::isOffscreenFrom() {
    int out = SceneSide::None;
    QRect sceneRect = level->grid->sceneRect().toRect();

    if (x() > sceneRect.right() ) out |= SceneSide::Right;
    if (y() > sceneRect.bottom()) out |= SceneSide::Down;

    // don't run the rest of the checks if 2 last ones said yes
    if (out == (SceneSide::Right | SceneSide::Down)) return (SceneSide) out;

    QPoint bottomRight = boundingRect().bottomRight().toPoint()+scenePos().toPoint();

    if (bottomRight.x() < 0) out |= SceneSide::Left;
    if (bottomRight.y() < 0) out |= SceneSide::Up;

    return (SceneSide) out;
}
