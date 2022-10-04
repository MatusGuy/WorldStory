#include "classes/gamedisplay.h"
#include "classes/gridscene.h"
#include "classes/tile.h"
#include "classes/level.h"

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

    //l->content[3]->setPos(QPoint(s.pointSpacing/2, s.pointSpacing/2));

    s.drawLoop();
    w.show();



    return a.exec();
}
