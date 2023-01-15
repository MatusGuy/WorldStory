#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QActionEvent>
#include <QActionGroup>

namespace WS::Creator {

class Toolbar : public QToolBar {
    public:
        Toolbar(QWidget *parent = nullptr);

        QAction* selected() const {return actionGroup.checkedAction();}

    protected:
        void actionEvent(QActionEvent *event);

    private:
        QActionGroup actionGroup;
};

}

#endif // TOOLBAR_H
