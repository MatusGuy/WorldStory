#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QSpinBox>

#if defined(WIN32) && defined(_MSC_VER)
    #include <winrt/Windows.UI.ViewManagement.h>
#endif

#include <level.h>

#include "viewport.h"
#include "attributeeditor.h"
#include "toolbar.h"
#include "writer.h"

#include "tools/pencil.h"
#include "tools/selectiontool.h"
#include "tools/eraser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace WS::Creator {

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        void loadFile(QFile* f);
        void loadLevel(WS::Levels::Level* lvl);
        void unloadLevel();
        void writeFile();
        WS::Levels::Level* loadedLevel();

        WS::Creator::Viewport viewport;

        public slots:
            void chooseFile();

    protected:
        void keyPressEvent(QKeyEvent* event);

    private:
        QLabel cameraPosLabel;

        void loadStyle();
        QPalette appStyle;
        
        WS::Levels::Level* level;
        QFile* file;
        QString openDir;

        Ui::MainWindow* ui;

        AttributeEditor attributeEditor;

        Toolbar toolbar;
        QToolBar* toolSettings = nullptr;
        //QTreeWidgetItem* getAttributeEditorCells(QTreeWidget* treeWidget, QString name, QVariant& value);

};

}

#endif // MAINWINDOW_H
