#include "gamedisplay.h"

using namespace WS::Core;

GameDisplay::GameDisplay(QWidget *parent): QGraphicsView(parent) {
    resize(800,450);
    #ifdef WIN32
        setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    #endif
    setMaximumSize(size());
    setMinimumSize(size());

    QOpenGLWidget* gl = new QOpenGLWidget(this);
    QSurfaceFormat format;
    format.setSamples(4);
    gl->setFormat(format);
    setViewport(gl);

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
