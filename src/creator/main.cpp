#include <QCommandLineParser>
#include <QFile>

#include "classes/mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    QCommandLineParser cli;
    cli.setApplicationDescription("World Story game.");
    cli.addHelpOption();
    cli.addVersionOption();

    cli.addPositionalArgument("lvlfile", "Load passed level file.");

    cli.process(a);

    #ifndef __linux__
        QApplication::setStyle("Fusion");
    #endif

    WS::Creator::MainWindow mw;
    if (cli.isSet("lvlfile")) {
        QFile* lvl = new QFile(cli.value("lvlfile"));
        mw.loadFile(lvl);
        delete lvl;
    }
    mw.show();

    return QApplication::exec();
}
