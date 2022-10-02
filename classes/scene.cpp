#include "scene.h"

using namespace WS::Core;

Scene::Scene(QObject *parent): QGraphicsScene{parent} {
    setBackgroundBrush(QBrush(Qt::GlobalColor::black));
}

void Scene::drawLoop() {
    draw();
    QTimer::singleShot(15, this, &Scene::draw);
}
