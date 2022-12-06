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

    connect(
        ui->A_Delete, &QAction::triggered, [this]() {
            this->viewport.editorScene.world->place(this->viewport.editorScene.cursor.gridPos, nullptr);
        }
    );

    connect(
        &viewport.editorScene.cursor, &Cursor::selectionChanged, [this]() {
            Tile* selection = viewport.editorScene.cursor.selecting();
            if (selection == nullptr) {
                for (int r = 0; r < ui->AttributeTable->topLevelItemCount(); r++) {
                    const QTreeWidgetItem* item = ui->AttributeTable->topLevelItem(r);
                    if (item != nullptr) delete item;
                }
                //ui->AttributeTable->clear();
                //ui->AttributeTable.setrow                                                                                                                
                return;
            }

            const QStringList& attNames = selection->getAttributeNames();
            for (int i = 0; i < attNames.length(); i++) {
                QVariant val = selection->getAttribute(attNames[i]);
                ui->AttributeTable->addTopLevelItem(getAttributeEditorCells(
                    ui->AttributeTable,
                    attNames[i],
                    val
                ));
            }
        }
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
}

QTreeWidgetItem* MainWindow::getAttributeEditorCells(QTreeWidget* treeWidget, QString name, QVariant& value) {
    auto out = new QTreeWidgetItem();

    out->setText(0, name);

    switch ((QMetaType::Type) value.typeId()) {
        case QMetaType::QPoint: {
            QPoint point = value.toPoint();
            out->setText(1, QString("%1,%2").arg(point.x(), point.y()));
            
            auto xCell = new QTreeWidgetItem();
            xCell->setText(0, "X");
            QSpinBox* xSpinBox = new QSpinBox(treeWidget);
            treeWidget->setItemWidget(xCell, 1, xSpinBox);

            auto yCell = new QTreeWidgetItem();
            yCell->setText(0, "Y");
            QSpinBox* ySpinBox = new QSpinBox(treeWidget);
            treeWidget->setItemWidget(yCell, 1, ySpinBox);

            out->addChildren({xCell, yCell});

            break;
        }

        /*
        case QMetaType::QUrl:
            QUrl url = value.toUrl();
            // TODO: Button that prompts with file
        */

        default: {
            out->setText(1, value.toString());
        }
    }

    return out;
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

