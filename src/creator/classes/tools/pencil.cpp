#include "pencil.h"

using namespace WS::Creator;
using namespace WS::Graphics;

Pencil::Pencil(WS::Graphics::Grid* t, QObject *parent): WS::Creator::ITool(t,parent) {
    QDir tileTextures(":/textures/tiles/");
    for (const QFileInfo& tile : tileTextures.entryInfoList(QDir::Files)) {
        QToolButton* tileButton = new QToolButton;
        tileButton->setObjectName(tile.baseName());
        tileButton->setCheckable(true);
        buttonGroup.addButton(tileButton);
        tileButtons.append(tileButton);
    }
}

Pencil::~Pencil() {
    for (QToolButton* button : tileButtons) delete button;
}

void WS::Creator::Pencil::action(QPoint pos) {
    Tile* tile = new Tile;
    tile->gridPos = pos;
    tile->setPixmap(buttonGroup.checkedButton()->objectName());
    target->place(tile);
}

const QWidgetList& Pencil::settingsUi() {
    return (const QWidgetList&) tileButtons;
}
