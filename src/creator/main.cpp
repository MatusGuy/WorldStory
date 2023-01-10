#include <QCommandLineParser>
#include <QFile>

#include "classes/mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    QCommandLineParser cli;
    cli.setApplicationDescription("World Story game.");
    cli.addHelpOption();
    cli.addVersionOption();

    cli.addPositionalArgument("lvlfile", "Load passed level file.", "[lvlfile]");

    cli.process(a);

    #ifndef __linux__
        QApplication::setStyle("Fusion");
    #endif

    const QStringList args = cli.positionalArguments();

    WS::Creator::MainWindow mw;
    if (args.length() > 0) {
        QFile* lvl = new QFile(args[0]);
        mw.loadFile(lvl);
        delete lvl;
    }
    mw.show();

    return QApplication::exec();
}
