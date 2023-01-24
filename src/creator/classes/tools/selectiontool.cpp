#include "selectiontool.h"

using namespace WS::Creator;

SelectionTool::SelectionTool(EditorScene* s, QObject* parent): ITool(s, parent) {
    setText("Selection");
    setIcon(QIcon::fromTheme("edit-select"));
}

void SelectionTool::sceneEvent(QGraphicsSceneEvent* event) {
    qDebug() << event->type();
    switch (event->type()) {
        case QGraphicsSceneEvent::GraphicsSceneMousePress: {
            auto mouseEvent = (QGraphicsSceneMouseEvent*) event;
            if (!(mouseEvent->buttons() | Qt::LeftButton)) return;

            QPoint pos = scene->getGridPosFrom(mouseEvent->scenePos().toPoint());

            scene->cursor.select(scene->world->get(pos));
        }
    }
}

