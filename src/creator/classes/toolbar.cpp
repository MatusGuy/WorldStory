#include "toolbar.h"

using WS::Creator::Toolbar;

Toolbar::Toolbar(QWidget* parent):
    QToolBar(parent),
    actionGroup(this)
{
}

void Toolbar::actionEvent(QActionEvent *event) {
    if (event->type() == QEvent::ActionAdded) {
        QAction* action = event->action();
        action->setActionGroup(&actionGroup);
        action->setParent(&actionGroup);
        action->setCheckable(true);
    }
    QToolBar::actionEvent(event);
}
