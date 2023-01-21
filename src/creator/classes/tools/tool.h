#ifndef TOOL_H
#define TOOL_H

#include <QAction>
#include <QWidgetList>

#include "../editorscene.h"

namespace WS::Creator {

class ITool : public QAction {

    public:
        ITool(EditorScene* s, QObject *parent = nullptr):
            QAction(parent)
        {
            scene = s;
            setCheckable(true);
        }

        virtual void action(QPoint pos) = 0;
        virtual const QWidgetList* settingsUi() = 0;

        EditorScene* scene;
};

}

#endif // TOOL_H
