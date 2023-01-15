#ifndef TOOL_H
#define TOOL_H

#include <QAction>
#include <QWidgetList>

#include <grid.h>

namespace WS::Creator {

class ITool : public QAction {
    public:
        explicit ITool(WS::Graphics::Grid* t, QObject *parent = nullptr):
            QAction(parent)
        {
            target = t;
        }

        virtual void action(QPoint pos) = 0;
        virtual const QWidgetList& settingsUi() = 0;

        static const QString toolName() { return "tool"; }
        static const QIcon toolIcon() { return QIcon::fromTheme(""); }

    protected:
        WS::Graphics::Grid* target;
};

}

#endif // TOOL_H
