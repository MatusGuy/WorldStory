#include "classes/gamedisplay.h"
#include "classes/gridscene.h"
#include "classes/tile.h"

#include <QApplication>
#include <QPixmap>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    WS::Core::GameDisplay w;

    WS::Graphics::GridScene s;
    w.setScene(&s);

    WS::Graphics::Tile t(&s);
    t.setPixmap(QPixmap(":/test/tile.png"));

    s.drawLoop();
    w.show();

    return a.exec();
}
