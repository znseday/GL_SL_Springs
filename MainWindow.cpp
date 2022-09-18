#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "MyOpenGLWidget.h"

#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    wgtDrawGL = new MyOpenGLWidget;

//    this->centralWidget()->layout()->addWidget(wgtDrawGL);
    this->setCentralWidget(wgtDrawGL);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionFile_Exit_triggered()
{
    this->close();
}

