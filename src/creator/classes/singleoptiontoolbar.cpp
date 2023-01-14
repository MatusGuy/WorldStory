#include "singleoptiontoolbar.h"

SingleOptionToolBar::SingleOptionToolBar(QWidget* parent):
    QToolBar(parent),
    actionGroup(this)
{
}

void SingleOptionToolBar::actionEvent(QActionEvent *event) {
    if (event->type() == QEvent::ActionAdded) {
        QAction* action = event->action();
        action->setActionGroup(&actionGroup);
        action->setParent(&actionGroup);
        action->setCheckable(true);
    }
    QToolBar::actionEvent(event);
}
