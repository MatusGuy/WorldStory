#ifndef ERASER_H
#define ERASER_H

#include "tool.h"

namespace WS::Creator {

class Eraser : public WS::Creator::ITool {

    public:
        explicit Eraser(EditorScene* s, QObject *parent = nullptr);

        virtual void sceneEvent(QGraphicsSceneEvent *event);

    private:
        //Tile picture;

        bool down;
        QPoint gridPos;
};

}

#endif // ERASER_H
