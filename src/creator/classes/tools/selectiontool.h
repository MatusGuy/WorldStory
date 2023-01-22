#ifndef SELECTIONTOOL_H
#define SELECTIONTOOL_H

#include "tool.h"

namespace WS::Creator {

class SelectionTool : public WS::Creator::ITool {
    public:
        SelectionTool(EditorScene* s, QObject *parent = nullptr);

        virtual void action(QPoint pos);

    private:
        Cursor* cursor;
};

}

#endif // SELECTIONTOOL_H
