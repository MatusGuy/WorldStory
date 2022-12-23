#include "gamedisplay.h"

using namespace WS::Core;

GameDisplay::GameDisplay(QWidget *parent): QGraphicsView(parent) {
    resize(800,450);
    #ifdef WIN32
        setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    #endif
    setMaximumSize(size());
    setMinimumSize(size());

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QSurfaceFormat format;
    format.setSamples(4);
    glWidget.setFormat(format);
    setViewport(&glWidget);

    setFrameShape(Shape::NoFrame);
    setFocusPolicy(Qt::FocusPolicy::StrongFocus);
}

GameDisplay::~GameDisplay() {

}

void GameDisplay::setScene(QGraphicsScene* scene) {
    QGraphicsView::setScene(scene);

    // no auto scrolling & 0,0 becomes top left instead of center
    scene->setSceneRect(rect());
    //resize(scene->itemsBoundingRect().size().toSize());
}
