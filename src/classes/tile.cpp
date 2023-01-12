#include "tile.h"
#include "gridscene.h"

using namespace WS::Graphics;

Tile::Tile() : WS::Levels::ILevelElement() {
    //setCacheMode(CacheMode::DeviceCoordinateCache);
    setupAttributes();
    gridPos.setX(0);
    gridPos.setY(0);
}

QRectF Tile::boundingRect() const {
    return QRectF(0, 0, size, size);
}

void Tile::paint(
    QPainter* painter,
    const QStyleOptionGraphicsItem* option,
    QWidget* widget
) {
    Q_UNUSED(widget);
    Q_UNUSED(option);

    if (isOffscreenFrom() != SceneSide::None) return;

    QRectF geo = boundingRect();

    painter->drawPixmap(geo.toRect(), pixmap());

    //QGraphicsObject::paint(painter, option, widget);
}

SceneSide Tile::isOffscreenFrom() {
    int out = SceneSide::None;
    QRect sceneRect = scene()->sceneRect().toRect();

    if (x() > sceneRect.right()) out |= SceneSide::Right;
    if (y() > sceneRect.bottom()) out |= SceneSide::Down;

    // don't run the rest of the checks if 2 last ones said yes
    if (out == (SceneSide::Right | SceneSide::Down)) return (SceneSide)out;

    QPoint bottomRight = boundingRect().bottomRight().toPoint() + scenePos().toPoint();

    if (bottomRight.x() < 0) out |= SceneSide::Left;
    if (bottomRight.y() < 0) out |= SceneSide::Up;

    return (SceneSide)out;
}

void Tile::setupAttributes() {
    attributeNames.append("pos");
    attributeNames.append("img");
}

void Tile::setAttribute(QString name, QString value) {
    QVariant oldVal = getAttribute(name);

    switch (attributeNames.indexOf(name)) {
        case -1:
            qCritical() << "attribute " + name + " not found";
            break;

        // pos
        case 0: {
            QStringList pos = value.split(',');
            int x = pos[0].toInt();
            int y = pos[1].toInt();

            if ((x < 0) || (y < 0)) return;

            if (world != nullptr) {
                world->move(this, x, y);
            } else {
                gridPos.setX(x);
                gridPos.setY(y);
            }
            break;
        }

        // img
        case 1: {
            setPixmap(value);
            break;
        }
    }

    emit attributeChanged(name, oldVal, getAttribute(name));
}

QVariant Tile::getAttribute(QString name) {
    switch (attributeNames.indexOf(name)) {
        case -1:
            qCritical() << "attribute " + name + " not found";
            break;

        // pos
        case 0: return QVariant(gridPos);

        // img
        case 1: return QVariant(pixId);
    }

    return QVariant();
}
