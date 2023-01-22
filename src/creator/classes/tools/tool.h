#ifndef TOOL_H
#define TOOL_H

#include <QAction>
#include <QToolBar>

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
        ~ITool() {
            if (settingsBar != nullptr) delete settingsBar;
        }

        virtual void action(QPoint pos) = 0;

        EditorScene* scene;
        QToolBar* settingsBar = nullptr;
};

}

#endif // TOOL_H
