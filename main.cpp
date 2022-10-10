#include "classes/gamedisplay.h"
#include "classes/gridscene.h"

#include <QApplication>
#include <QPixmap>
#include <QFile>
#include <QPoint>

namespace WS::Core {
    inline void launchGame() {
        WS::Core::GameDisplay w;

        WS::Graphics::GridScene s(&w);
        w.setScene(&s);

        WS::Levels::Level* l = WS::Levels::loadLevel(new QFile(":/test/levels/testLevel.xml"));
        s.setLevel(l);

        //l->content[1]->setPos(QPoint(0, s.pointSpacing));

        s.drawLoop();
        w.show();
    }

    inline void launchCreator(QApplication* app) {
        app->
    }
}

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);



    return a.exec();
}
