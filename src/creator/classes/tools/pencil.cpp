#include "pencil.h"

using namespace WS::Creator;
using namespace WS::Graphics;

Pencil::Pencil(EditorScene* s, QObject *parent): WS::Creator::ITool(s,parent) {
    setText("Pencil");
    setIcon(QIcon::fromTheme("edit"));

    settingsBar = new QToolBar;

    QDir tileTextureDir(":/textures/tiles/");
    QFileInfoList tileTextures = tileTextureDir.entryInfoList(QDir::Files);
    for (int i = 0; i<tileTextures.length(); i++) {
        QToolButton* tileButton = new QToolButton(settingsBar);
        QFileInfo texture = tileTextures[i];
        tileButton->setObjectName(texture.baseName());
        tileButton->setCheckable(true);
        tileButton->setIcon(QIcon(texture.absoluteFilePath()));
        buttonGroup.addButton(tileButton);
        settingsBar->addWidget(tileButton);
        if (i==0) tileButton->setChecked(true);
    }

    /*
    QToolButton* defaultTile = buttonGroup.set;
    defaultTile->setChecked(true);
    */
}

void Pencil::sceneEvent(QGraphicsSceneEvent *event) {
    switch (event->type()) {
        case QGraphicsSceneEvent::GraphicsSceneMousePress: {
            auto mouseEvent = (QGraphicsSceneMouseEvent*) event;
            if (!(mouseEvent->buttons() | Qt::LeftButton)) return;

            down = true;

            QPoint pos = scene->getGridPosFrom(mouseEvent->scenePos().toPoint());
            gridPos = pos;

            placeAt(pos);

            break;
        }
        case QGraphicsSceneEvent::GraphicsSceneMouseMove: {
            if (!down) return;

            auto mouseEvent = (QGraphicsSceneMouseEvent*) event;

            QPoint pos = scene->getGridPosFrom(mouseEvent->scenePos().toPoint());
            if (gridPos == pos) return;
            gridPos = pos;

            placeAt(pos);

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

void Pencil::placeAt(QPoint& pos) {
    scene->world->remove(scene->world->get(pos));
    Tile* tile = new Tile;
    tile->gridPos = pos;
    tile->setAttribute("img", buttonGroup.checkedButton()->objectName());
    scene->world->place(tile);
}
