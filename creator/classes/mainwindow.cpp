#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace WS::Creator;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    ui = new Ui::MainWindow;
    ui->setupUi(this);

    ui->L_MainLayout->addWidget(&viewport);
}

MainWindow::~MainWindow() {
    delete ui;
}

