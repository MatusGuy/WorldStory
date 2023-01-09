#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace WS::Creator;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    ui = new Ui::MainWindow;
    ui->setupUi(this);

    #ifndef __linux__
    loadStyle();
    #endif

    setWindowTitle("WorldStoryCreator");
    grabKeyboard();

    ui->L_MainLayout->addWidget(&viewport);

    delete ui->D_Attributes->widget();
    ui->D_Attributes->setWidget(&attributeEditor);

    viewport.editorScene.tileMenu.addActions(ui->M_Edit->actions());

    cameraPosLabel.setText("Camera: 0,0");
    ui->StatusBar->addPermanentWidget(&cameraPosLabel);

    connect(
        ui->A_Open, &QAction::triggered,
        this, &MainWindow::chooseFile
    );

    connect(
        ui->A_Delete, &QAction::triggered, [this]() {
            WS::Graphics::Grid* world = viewport.editorScene.world;
            world->remove(world->get(viewport.editorScene.cursor.gridPos));
        }
    );

    connect(
        &viewport.editorScene.cursor, &Cursor::selectionChanged, [this]() {
            Tile* selection = viewport.editorScene.cursor.selecting();
            attributeEditor.loadElement(selection);
        }
    );

    connect(
        &viewport.editorScene, &EditorScene::tileDragFinished, [this](Tile* tile) {
            attributeEditor.updateProperties();
        }
    );

    connect(
        ui->A_AboutQt, &QAction::triggered,
        QApplication::instance(), &QApplication::aboutQt
    );

    openDir = QDir::homePath();

    level = nullptr;
    file = nullptr;
}

MainWindow::~MainWindow() {
    if (level != nullptr) unloadLevel();
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
    //qDebug() << "pressed";
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

    
    cameraPosLabel.setText(QString("Camera: %1,%2").arg(viewport.editorScene.camGridPos().x()).arg(viewport.editorScene.camGridPos().y()));
}

void MainWindow::loadStyle() {
    QColor darkGray(53, 53, 53);
    QColor gray(128, 128, 128);
    QColor black(25, 25, 25);
    QColor blue(42, 130, 218);

    appStyle.setColor(QPalette::Window, darkGray);
    appStyle.setColor(QPalette::WindowText, Qt::white);
    appStyle.setColor(QPalette::Base, black);
    appStyle.setColor(QPalette::AlternateBase, darkGray);
    appStyle.setColor(QPalette::ToolTipBase, blue);
    appStyle.setColor(QPalette::ToolTipText, Qt::white);
    appStyle.setColor(QPalette::Text, Qt::white);
    appStyle.setColor(QPalette::Button, darkGray);
    appStyle.setColor(QPalette::ButtonText, Qt::white);
    appStyle.setColor(QPalette::Link, blue);
    appStyle.setColor(QPalette::HighlightedText, Qt::black);

    appStyle.setColor(QPalette::Active, QPalette::Button, gray.darker());
    appStyle.setColor(QPalette::Disabled, QPalette::ButtonText, gray);
    appStyle.setColor(QPalette::Disabled, QPalette::WindowText, gray);
    appStyle.setColor(QPalette::Disabled, QPalette::Text, gray);
    appStyle.setColor(QPalette::Disabled, QPalette::Light, darkGray);

    #if defined(WIN32) && defined(_MSC_VER)
    winrt::Windows::UI::ViewManagement::UISettings const ui_settings{};
    auto const accent_color{ ui_settings.GetColorValue(
            winrt::Windows::UI::ViewManagement::UIColorType::Accent
    )};
    appStyle.setColor(QPalette::Highlight, QColor(
        accent_color.R,
        accent_color.G,
        accent_color.B,
        accent_color.A
    ));
    #else
    appStyle.setColor(QPalette::Highlight, blue);
    #endif

    QApplication::setPalette(appStyle);
}

void MainWindow::loadFile(QFile* f) {
    Levels::Level* level = WS::Levels::loadLevel(f);

    if (level == nullptr) {
        QString err =
            "An error has occured while loading the chosenlevel file"
            "\n\nFile: %1"
            "\nError: %2 (%3)";
        err = err.arg(f->fileName(), Levels::xmlReader.errorString(), QString::number((int)Levels::xmlReader.error()));
        QMessageBox::critical(
            this,
            "Error occured loading level!",
            err,
            QMessageBox::StandardButton::Ok
        );
        return;
    }

    file = f;
    openDir = QFileInfo(file->fileName()).dir().path();

    loadLevel(level);
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
    file = nullptr;
    //delete file;
}

WS::Levels::Level* MainWindow::loadedLevel() {
    return level;
}

