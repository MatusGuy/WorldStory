#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "creator/classes/viewport.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace WS::Creator {

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        WS::Creator::Viewport viewport;

    private:
        Ui::MainWindow* ui;
};

}

#endif // MAINWINDOW_H
