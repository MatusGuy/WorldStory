#include "tilefield.h"

using namespace WS::Graphics;

TileField::TileField(Levels::Level* lvl): Tile(lvl) {}

QRectF TileField::boundingRect() const {
    return QRectF(QPoint(0,0),size*level->grid->pointSpacing);
}

void TileField::paint(
    QPainter* painter,
    const QStyleOptionGraphicsItem* option,
    QWidget* widget
) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPoint realsize = boundingRect().bottomRight().toPoint();
    const int& ps = level->grid->pointSpacing;

    for (int dy = 0; dy < realsize.y(); dy += ps) {
        for (int dx = 0; dx < realsize.x(); dx += ps) {
            QRect geo(dx,dy , ps,ps);
            painter->drawPixmap(geo, pixmap());
            painter->drawRect(boundingRect());
        }
    }
}
