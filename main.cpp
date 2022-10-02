#include "classes/gamedisplay.h"
#include "classes/gridscene.h"
#include "classes/tile.h"
#include "classes/level.h"

#include <QApplication>
#include <QPixmap>
#include <QFile>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    WS::Core::GameDisplay w;

    WS::Graphics::GridScene s;
    w.setScene(&s);

    WS::Graphics::Tile t(&s);
    t.setPixmap(QPixmap(":/test/textures/tile.png"));

    s.drawLoop();
    w.show();

    WS::Levels::loadLevel(new QFile(":/test/levels/testLevel.xml"));

    return a.exec();
}
