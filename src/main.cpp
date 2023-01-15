#include <QApplication>
#include <QCommandLineParser>
#include <QFile>
#include <QPoint>

#include "classes/gamedisplay.h"
#include "classes/gridscene.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    a.setApplicationName(__WS_NAME__);
    a.setApplicationDisplayName(__WS_NAME__);
    a.setApplicationVersion(__WS_VERSION__);

    WS::Core::GameDisplay w;

    WS::Graphics::GridScene s(&w);
    w.setScene(&s);

    QFile lf(":/levels/testLevel.xml");
    WS::Levels::Level* l = WS::Levels::loadLevel(&lf);

    if (l == nullptr) {
        qCritical() << "Error loading level:" << WS::Levels::xmlReader.errorString();
        return 1;
    }

    s.setLevel(l);

    // l->content[1]->setPos(QPoint(0, s.pointSpacing));

    s.drawLoop();
    w.show();

    int resp = QApplication::exec();

    delete l;

    return resp;
}
