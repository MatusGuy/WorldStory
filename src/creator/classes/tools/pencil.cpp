#include "pencil.h"

using namespace WS::Creator;
using namespace WS::Graphics;

Pencil::Pencil(EditorScene* s, QObject *parent): WS::Creator::ITool(s,parent) {
    setText("Pencil");
    setIcon(QIcon::fromTheme("edit"));

    QDir tileTextures(":/textures/tiles/");
    for (const QFileInfo& tile : tileTextures.entryInfoList(QDir::Files)) {
        QToolButton* tileButton = new QToolButton;
        tileButton->setObjectName(tile.baseName());
        tileButton->setCheckable(true);
        buttonGroup.addButton(tileButton);
        tileButtons.append(tileButton);
    }

    QToolButton* defaultTile = tileButtons[0];
    defaultTile->setChecked(true);
}

Pencil::~Pencil() {
    for (QToolButton* button : tileButtons) delete button;
}

void Pencil::action(QPoint pos) {
    Tile* tile = new Tile;
    tile->gridPos = pos;
    tile->setPixmap(buttonGroup.checkedButton()->objectName());
    scene->world->place(tile);
}

const QWidgetList* Pencil::settingsUi() {
    return (const QWidgetList*) &tileButtons;
}