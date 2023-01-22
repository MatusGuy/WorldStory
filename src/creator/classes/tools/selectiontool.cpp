#include "selectiontool.h"

using namespace WS::Creator;

SelectionTool::SelectionTool(EditorScene* s, QObject* parent): ITool(s, parent) {
    setText("Selection");
    setIcon(QIcon::fromTheme("edit-select"));
}

void SelectionTool::action(QPoint pos) {
    scene->cursor.select(scene->world->get(pos));
}

