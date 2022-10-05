#include "classes/gamedisplay.h"
#include "classes/gridscene.h"

#include <QApplication>
#include <QPixmap>
#include <QFile>
#include <QPoint>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    WS::Core::GameDisplay w;

    WS::Graphics::GridScene s(&w);
    w.setScene(&s);

    WS::Levels::Level* l = WS::Levels::loadLevel(new QFile(":/test/levels/testLevel.xml"));
    s.setLevel(l);

    /*
    WS::Graphics::Tile t(&l);
    t.setPixmap(QPixmap(":/test/textures/tile.png"));
    */

    //l->content[1]->setPos(QPoint(0, s.pointSpacing));

    s.drawLoop();
    w.show();



    return a.exec();
}
