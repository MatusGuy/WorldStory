#include "scene.h"

using namespace WS::Core;

Scene::Scene(QObject *parent): QGraphicsScene{parent} {
    setBackgroundBrush(QBrush(Qt::GlobalColor::white));


}

void Scene::drawLoop() {
    draw();
    QTimer::singleShot(75, this, &Scene::drawLoop);
}
