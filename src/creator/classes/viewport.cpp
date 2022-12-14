#include "viewport.h"

using WS::Creator::Viewport;

Viewport::Viewport(QWidget* parent): WS::Core::GameDisplay{parent} {
    setScene(&editorScene);
    editorScene.viewport = this;
    setBackgroundBrush(QBrush(Qt::black));
    //setCacheMode(QGraphicsView::CacheBackground);
}
