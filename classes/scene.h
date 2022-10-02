#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>

namespace WS {

namespace Core {

class Scene : public QGraphicsScene {
    public:
        explicit Scene(QObject *parent = nullptr);

        public slots:
            void drawLoop();

    protected:

        protected slots:
            virtual void draw() = NULL;

};

}

}

#endif // SCENE_H
