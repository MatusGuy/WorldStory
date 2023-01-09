#include "scenegridoverlay.h"

using namespace WS::Creator;

SceneGridOverlay::SceneGridOverlay(EditorScene* e): QGraphicsRectItem() {
    editor = e;

    gridPen.setColor(QColor::fromHsv(0,0,100,floor(255/2)));
    gridPen.setWidth(2);
}

void SceneGridOverlay::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(gridPen);

    int tileSize = editor->tileSize;
    QRect sceneRect = rect().toRect();

    for (int x = 0; x < sceneRect.size().width(); x += tileSize) {
        painter->drawLine(
            x,
            0,
            x,
            sceneRect.size().height()
        );
    }

    for (int y = 0; y < sceneRect.size().height(); y += tileSize) {
        painter->drawLine(
            0,
            y,
            sceneRect.size().width(),
            y
        );
    }
}
