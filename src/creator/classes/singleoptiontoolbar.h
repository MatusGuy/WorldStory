#ifndef SINGLEOPTIONTOOLBAR_H
#define SINGLEOPTIONTOOLBAR_H

#include <QToolBar>
#include <QActionEvent>
#include <QActionGroup>

class SingleOptionToolBar : public QToolBar {
    public:
        SingleOptionToolBar(QWidget *parent = nullptr);

        QAction* selected() const {return actionGroup.checkedAction();}

    protected:
        void actionEvent(QActionEvent *event);

    private:
        QActionGroup actionGroup;
};

#endif // SINGLEOPTIONTOOLBAR_H
