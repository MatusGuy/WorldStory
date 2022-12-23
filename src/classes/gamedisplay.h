#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H

#include <QGraphicsView>

#include <QOpenGLWidget>

namespace WS::Core {

class GameDisplay : public QGraphicsView {
    Q_OBJECT

    public:
        GameDisplay(QWidget *parent = nullptr);
        ~GameDisplay();

        void setScene(QGraphicsScene* scene);

    private:
        QOpenGLWidget glWidget;
};

}

#endif // GAMEDISPLAY_H
