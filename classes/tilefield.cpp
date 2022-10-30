#include "tilefield.h"

using namespace WS::Graphics;

TileField::TileField(WS::Levels::Level* lvl) : Tile(lvl) {}

QRectF TileField::boundingRect() const {
    return QRectF(QPoint(0, 0), size * level->grid->tileSize);
}

void TileField::paint(
    QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget
) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    const int& ps = level->grid->tileSize;

    /**
     * @var dx
     * @brief x draw cursor
     */
    /**
     * @var dy
     * @brief y draw cursor
     */
    int dx = 0, dy = 0;

    QPoint realsize = boundingRect().bottomRight().toPoint();
    // QPoint bottomRight = realsize+scenePos().toPoint();

    // completely offscreen? don't draw.
    if (isOffscreenFrom() != SceneSide::None) return;

    // if at least one tile is offscreen
    if (x() + ps <= 0) {
        // look for first tile onscreen
        // and set it's x position to the x draw cursor
        for (dx = ps; dx + x() < -ps; dx += ps) assert(dx < realsize.x());
    }

    // if at least one tile is offscreen
    if (y() + ps <= 0) {
        // look for first tile onscreen
        // and set it's y position to the y draw cursor
        for (dy = ps; dy + y() < -ps; dy += ps) assert(dy < realsize.y());
    }

    QRect sceneRect = level->grid->sceneRect().toRect();

    for (; dy < realsize.y(); dy += ps) {
        if (dy + y() - ps >= sceneRect.height()) break;

        for (; dx < realsize.x(); dx += ps) {
            if (dx + x() >= sceneRect.width()) break;

            QRect geo(dx, dy, ps, ps);

            painter->drawPixmap(geo, pixmap());
        }
    }
}
