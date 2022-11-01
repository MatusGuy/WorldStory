#include "cursor.h"

using namespace WS::Creator;

Cursor::Cursor() {
    highlightBrush.setColor(QColor(255, 240, 0, 115));
    cornerBrush.setColor(QColor(255, 240, 0));
}

void Cursor::paint(
    QPainter* painter,
    const QStyleOptionGraphicsItem* option,
    QWidget* widget
) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setBrush(highlightBrush);

    QRectF geo = boundingRect();
    painter->drawRect(geo);

    painter->setBrush(cornerBrush);

    int lineLimit = size/3;

    //top left
    painter->drawLine(0,0,lineLimit,0); // hor
    painter->drawLine(0,0,0,lineLimit); // ver

    // top right
    painter->drawLine(1,0,1-lineLimit,0); // hor
    painter->drawLine(1,0,1,lineLimit); // ver

    // bottom left
    painter->drawLine(0,1,lineLimit,1); // hor
    painter->drawLine(0,1,0,1-lineLimit); // ver

    // bottom right
    painter->drawLine(1,1,1-lineLimit,1); // hor
    painter->drawLine(1,1,1,1-lineLimit); // ver
}
