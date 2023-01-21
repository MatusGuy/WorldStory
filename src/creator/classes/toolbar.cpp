#include "toolbar.h"

using namespace WS::Creator;

Toolbar::Toolbar(QWidget* parent):
    QToolBar(parent),
    actionGroup(this)
{
}

void Toolbar::actionEvent(QActionEvent *event) {
    if (event->type() == QEvent::ActionAdded) {
        ITool* action = (ITool*) event->action();
        action->setActionGroup(&actionGroup);
        action->setParent(&actionGroup);
    }
    QToolBar::actionEvent(event);
}
