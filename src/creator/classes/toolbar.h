#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QActionEvent>
#include <QActionGroup>

#include "tools/tool.h"

namespace WS::Creator {

class Toolbar : public QToolBar {
    public:
        Toolbar(QWidget *parent = nullptr);

        ITool* selected() const {return (ITool*) actionGroup.checkedAction();}

        QActionGroup actionGroup;

    protected:
        void actionEvent(QActionEvent *event);
};

}

#endif // TOOLBAR_H
