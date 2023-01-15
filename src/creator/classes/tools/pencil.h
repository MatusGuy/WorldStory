#ifndef PENCIL_H
#define PENCIL_H

#include <QToolButton>
#include <QButtonGroup>
#include <QDir>

#include "tool.h"

namespace WS::Creator {

class Pencil : public WS::Creator::ITool {

    public:
        explicit Pencil(WS::Graphics::Grid* t, QObject *parent = nullptr);
        ~Pencil();

        virtual void action(QPoint pos);
        const QWidgetList& settingsUi();

        static const QString toolName() {return "Pencil";}
        static const QIcon toolIcon() {return QIcon::fromTheme("");}

    private:
        //Tile picture;

        QButtonGroup buttonGroup;
        QList<QToolButton*> tileButtons;
};

}

#endif // PENCIL_H
