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

        virtual void action(QPoint pos);

    private:
        //Tile picture;

        QButtonGroup buttonGroup;
};

}

#endif // PENCIL_H
