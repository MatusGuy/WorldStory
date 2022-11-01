#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace WS::Creator;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    ui = new Ui::MainWindow;
    ui->setupUi(this);

    setWindowTitle("WorldStoryCreator");
    grabKeyboard();

    ui->L_MainLayout->addWidget(&viewport);

    connect(
        ui->A_Open, &QAction::triggered,
        this, &MainWindow::chooseFile
    );

    openDir = QDir::homePath();

    level = nullptr;
}

MainWindow::~MainWindow() {
    unloadLevel();
    delete ui;
}

void MainWindow::chooseFile() {
    QString chosen = QFileDialog::getOpenFileName(
        this,
        "Open level file...",
        openDir,
        "Levels (*.xml)"
    );

    if (!chosen.isEmpty()) loadFile(new QFile(chosen));
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    qDebug() << "pressed";
    switch (event->key()) {
        case Qt::Key_A:
            viewport.editorScene.cameraPos.rx() -= 5;
            break;

        case Qt::Key_D:
            viewport.editorScene.cameraPos.rx() += 5;
            break;

        case Qt::Key_W:
            viewport.editorScene.cameraPos.ry() -= 5;
            break;

        case Qt::Key_S:
            viewport.editorScene.cameraPos.ry() += 5;
            break;

        default:
            break;
    }
}

void MainWindow::loadFile(QFile* f) {
    file = f;
    openDir = QFileInfo(file->fileName()).dir().path();
    loadLevel(WS::Levels::loadLevel(file));
}

void MainWindow::loadLevel(Levels::Level* lvl) {
    if (level != nullptr) unloadLevel();

    level = lvl;
    setWindowTitle(level->name + " - WorldStoryCreator");
    viewport.editorScene.setLevel(level);
    viewport.editorScene.drawLoop();
}

void MainWindow::unloadLevel() {
    setWindowTitle("WorldStoryCreator");
    delete level;
    delete file;
}

WS::Levels::Level* MainWindow::loadedLevel() {
    return level;
}

