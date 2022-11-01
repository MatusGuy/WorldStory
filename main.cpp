#include <QApplication>
#include <QCommandLineParser>
#include <QFile>
#include <QPoint>

#include "classes/gamedisplay.h"
#include "classes/gridscene.h"
#include "creator/classes/mainwindow.h"

bool applyStyle(QString sheetname) {
    QFile stylesheet(sheetname);
    QApplication* app = ((QApplication*)QApplication::instance());
    if (stylesheet.open(QFile::ReadOnly)) {
        app->setStyleSheet(stylesheet.readAll());
        stylesheet.close();
        return true;
    }
    return false;
}

namespace WS::Core {

int launchGame() {
    WS::Core::GameDisplay w;

    WS::Graphics::GridScene s(&w);
    w.setScene(&s);

    QFile lf(":/test/levels/testLevel.xml");
    WS::Levels::Level* l = WS::Levels::loadLevel(&lf);
    s.setLevel(l);

    // l->content[1]->setPos(QPoint(0, s.pointSpacing));

    s.drawLoop();
    w.show();

    int resp = QApplication::exec();

    delete l;

    return resp;
}

int launchCreator() {
    QApplication::setStyle("Fusion");
    applyStyle(":/creator/style/appstyle.qss");

    WS::Creator::MainWindow w;
    QApplication::setActiveWindow((QWidget*) &w);
    w.show();

    return QApplication::exec();
}

int launchCreator(QFile levelFile) {
    // later adding code for loading level file on main window class
    QApplication::setStyle("Fusion");
    applyStyle(":/creator/style/appstyle.qss");

    WS::Creator::MainWindow w;
    w.loadFile(&levelFile);
    QApplication::setActiveWindow((QWidget*) &w);
    w.show();

    return QApplication::exec();
}

}  // namespace WS::Core

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    a.setApplicationName(__NAME__);
    a.setApplicationDisplayName(__NAME__);
    a.setApplicationVersion(__VERSION__);

    QCommandLineParser cli;
    cli.setApplicationDescription("World Story game");
    cli.addHelpOption();
    cli.addVersionOption();

    QCommandLineOption creatorOption(
        QStringList() << "c"
                      << "creator",
        R"(Open creator on <levelFile> instead of game. If <levelFile> is "none" then open creator on an empty level)",
        "levelFile"
    );
    cli.addOption(creatorOption);

    cli.process(a);

    if (cli.isSet(creatorOption)) {
        QString levelFile = cli.value(creatorOption);
        if (levelFile == "none")
            return WS::Core::launchCreator();
        else
            return WS::Core::launchCreator(QFile(levelFile));
    } else
        return WS::Core::launchGame();
}
