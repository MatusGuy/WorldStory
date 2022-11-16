#include "cursor.h"

using namespace WS::Creator;

Cursor::Cursor() {
    setZValue(2);
    unselect();

    highlightPen.setColor(QColor(255, 240, 0, 70));
    cornerPen.setColor(QColor(255, 240, 0));
    cornerPen.setWidth(3);
}

void Cursor::select(Tile* tile) {
    if (tile == nullptr) {
        unselect();
        return;
    }

    selecting = tile;
    show();
    setPos(tile->pos());
    update();
}

void Cursor::unselect() {
    selecting = nullptr;
    hide();
    update();
}

void Cursor::paint(
    QPainter* painter,
    const QStyleOptionGraphicsItem* option,
    QWidget* widget
) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(highlightPen);

    QRectF geo = boundingRect();
    painter->drawRect(geo);
    painter->fillRect(geo, highlightPen.color());

    painter->setPen(cornerPen);

    int lineLimit = size/3;

    //top left
    painter->drawLine(0,0,lineLimit,0); // hor
    painter->drawLine(0,0,0,lineLimit); // ver

    // top right
    painter->drawLine(size,0,size-lineLimit,0); // hor
    painter->drawLine(size,0,size,lineLimit); // ver

    // bottom left
    painter->drawLine(0,size,lineLimit,size); // hor
    painter->drawLine(0,size,0,size-lineLimit); // ver

    // bottom right
    painter->drawLine(size,size,size-lineLimit,size); // hor
    painter->drawLine(size,size,size,size-lineLimit); // ver
}
