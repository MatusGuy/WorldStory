#include "scenegridoverlay.h"

using namespace WS::Creator;

SceneGridOverlay::SceneGridOverlay(EditorScene* e): QGraphicsItem() {
    editor = e;

    gridPen.setColor(QColor(Qt::white));
    gridPen.setWidth(3);
}

QRectF SceneGridOverlay::boundingRect() const {
    return QRectF();
    //return scene()->sceneRect();
}

void SceneGridOverlay::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(gridPen);

    int tileSize = editor->tileSize;
    QRect sceneRect = boundingRect().toRect();

    for (int x = sceneRect.topLeft().x(); x < sceneRect.bottomLeft().x(); x += tileSize) {
        painter->drawLine(x, sceneRect.topLeft().y(), x, sceneRect.bottomLeft().y());
    }

    for (int y = sceneRect.topLeft().y(); y < sceneRect.bottomLeft().y(); y += tileSize) {
        painter->drawLine(sceneRect.topLeft().x(), y, sceneRect.topLeft().x(), y);
    }
}
