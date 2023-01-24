#include "eraser.h"

using namespace WS::Creator;
using namespace WS::Graphics;

Eraser::Eraser(EditorScene* s, QObject *parent): WS::Creator::ITool(s,parent) {
    setText("Eraser");
    setIcon(QIcon::fromTheme("edit-erase"));
}

void Eraser::sceneEvent(QGraphicsSceneEvent *event) {
    switch (event->type()) {
        case QGraphicsSceneEvent::GraphicsSceneMousePress: {
            auto mouseEvent = (QGraphicsSceneMouseEvent*) event;
            if (!(mouseEvent->buttons() | Qt::LeftButton)) return;

            down = true;

            QPoint pos = scene->getGridPosFrom(mouseEvent->scenePos().toPoint());
            gridPos = pos;

            scene->world->remove(scene->world->get(pos));

            break;
        }
        case QGraphicsSceneEvent::GraphicsSceneMouseMove: {
            if (!down) return;

            auto mouseEvent = (QGraphicsSceneMouseEvent*) event;

            QPoint pos = scene->getGridPosFrom(mouseEvent->scenePos().toPoint());
            if (gridPos == pos) return;
            gridPos = pos;

            scene->world->remove(scene->world->get(pos));

            break;
        }
        case QGraphicsSceneEvent::GraphicsSceneMouseRelease: {
            auto mouseEvent = (QGraphicsSceneMouseEvent*) event;
            if (!(mouseEvent->buttons() | Qt::LeftButton)) return;

            down = false;

            break;
        }
    }
}
