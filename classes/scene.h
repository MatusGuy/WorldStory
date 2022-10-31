#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QtDebug>
#include <QLabel>

#include <ctime>
#include <sstream>

namespace WS {

namespace Core {

class Scene : public QGraphicsScene {
    public:
        explicit Scene(QObject *parent = nullptr);

        int frames;
        std::time_t initTime;
        QLabel fps;
        bool loopStarted = false;

        public slots:
            void drawLoop();

    protected:

        protected slots:
            virtual void draw() = NULL;

};

}

}

#endif // SCENE_H
