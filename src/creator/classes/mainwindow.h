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
        WS::Levels::Level* loadedLevel();

        WS::Creator::Viewport viewport;

        public slots:
            void chooseFile();

    protected:
        void keyPressEvent(QKeyEvent* event);

    private:
        void loadStyle();
        QPalette appStyle;
        
        WS::Levels::Level* level;
        QFile* file;
        QString openDir;

        Ui::MainWindow* ui;

        AttributeEditor attributeEditor;
        //QTreeWidgetItem* getAttributeEditorCells(QTreeWidget* treeWidget, QString name, QVariant& value);

};

}

#endif // MAINWINDOW_H
