#ifndef PENCIL_H
#define PENCIL_H

#include <QToolButton>
#include <QButtonGroup>
#include <QDir>

#include "tool.h"

namespace WS::Creator {

class Pencil : public WS::Creator::ITool {

    public:
        explicit Pencil(EditorScene* s, QObject *parent = nullptr);

        virtual void sceneEvent(QGraphicsSceneEvent *event);

    private:
        //Tile picture;

        QButtonGroup buttonGroup;
        bool down;
        QPoint gridPos;

        void placeAt(QPoint& pos);
};

}

#endif // PENCIL_H
