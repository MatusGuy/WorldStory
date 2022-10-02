#include "gamedisplay.h"

using namespace WS::Core;

GameDisplay::GameDisplay(QWidget *parent): QGraphicsView(parent) {
    resize(600,500);
    #ifdef WIN32
        setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    #endif
    setMaximumSize(size());
    setMinimumSize(size());

    setFrameShape(Shape::NoFrame);
    setFocusPolicy(Qt::FocusPolicy::StrongFocus);
}

GameDisplay::~GameDisplay() {

}

void GameDisplay::setScene(QGraphicsScene* scene) {
    QGraphicsView::setScene(scene);

    // no auto scrolling
    scene->setSceneRect(QRectF(rect()));

    setSceneRect(scene->sceneRect());
}
