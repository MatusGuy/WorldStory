#include "editorscene.h"

using namespace WS::Creator;

EditorScene::EditorScene(QObject *parent): WS::Graphics::GridScene{parent} {
    addItem(&cursor);
}

void EditorScene::draw() {
    WS::Graphics::GridScene::draw();

    cursor.setPos(0,0);
    cursor.update();
}
