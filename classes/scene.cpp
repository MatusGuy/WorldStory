#include "scene.h"

using namespace WS::Core;

Scene::Scene(QObject *parent): QGraphicsScene{parent} {
    //setBackgroundBrush(QBrush(Qt::GlobalColor::white));
    std::time(&initTime);
    frames=0;
}

void Scene::drawLoop() {
    std::time_t currTime;
    int diffTime;
    draw();
    QTimer::singleShot(15, this, &Scene::drawLoop);
    frames++;

    std::time(&currTime);
    diffTime=currTime-initTime;

    if (diffTime>=1) {
        initTime=currTime;
        qDebug() <<currTime << " | " << frames<<"FPS";
        frames=0;
    }
}
