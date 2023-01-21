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
        ~Pencil();

        virtual void action(QPoint pos);
        const QWidgetList* settingsUi();

    private:
        //Tile picture;

        QButtonGroup buttonGroup;
        QList<QToolButton*> tileButtons;
};

}

#endif // PENCIL_H
