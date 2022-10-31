#include "scene.h"

using namespace WS::Core;

Scene::Scene(QObject *parent): QGraphicsScene{parent} {
    //setBackgroundBrush(QBrush(Qt::GlobalColor::white));
    fps.setWindowTitle("fps");
    fps.show();
    std::time(&initTime);
    frames=0;
}

void Scene::drawLoop() {
    loopStarted = true;
    std::time_t currTime;
    int diffTime;
    draw();
    QTimer::singleShot(15, this, &Scene::drawLoop);
    frames++;

    std::time(&currTime);
    diffTime=currTime-initTime;

    if (diffTime>=1) {
        initTime=currTime;

        //qDebug() <<currTime << " | " << frames<<"FPS";
        std::stringstream ss;
        ss<<currTime << " | " << frames<<"FPS";
        fps.setText(ss.str().c_str());
        frames=0;
    }
}
