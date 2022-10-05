#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H

#include <QGraphicsView>

#include <QOpenGLWidget>

namespace WS {

namespace Core {

class GameDisplay : public QGraphicsView {
    Q_OBJECT

    public:
        GameDisplay(QWidget *parent = nullptr);
        ~GameDisplay();

        void setScene(QGraphicsScene* scene);
};

}

}

#endif // GAMEDISPLAY_H
