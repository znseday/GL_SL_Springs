#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "MyOpenGLWidget.h"

#include <QLayout>
#include <QMessageBox>
#include <sstream>

static constexpr int Basic_dt = 1000/60.0 - 1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    wgtDrawGL = new MyOpenGLWidget;

    this->centralWidget()->layout()->addWidget(wgtDrawGL);
//    this->setCentralWidget(wgtDrawGL);
    connect(wgtDrawGL, SIGNAL(SignalSendCurrentFps(int)),
            this,   SLOT(SlotReceiveCurrentFps(int)));
}
//-------------------------------------------------------------

void MainWindow::SlotReceiveCurrentFps(int fps)
{
    this->setWindowTitle("fps = " + QString().setNum(fps));
}
//-------------------------------------------------------------

MainWindow::~MainWindow()
{
    delete ui;
}
//-------------------------------------------------------------

void MainWindow::on_actionFile_Exit_triggered()
{
    this->close();
}
//-------------------------------------------------------------

void MainWindow::on_btnGo_clicked()
{
    PhyModelSettings ms;

    bool isOk = false;
    ms.m = ui->Edit_m->text().toDouble(&isOk);
    if (!isOk || ms.m <= 0 || ms.m > 100)
    {
        QMessageBox::critical(this, "Error", "Incorrect m");
        return;
    }

    isOk = false;
    ms.k1 = ui->Edit_k1->text().toDouble(&isOk);
    if (!isOk || ms.k1 <= 0 || ms.k1 > 100)
    {
        QMessageBox::critical(this, "Error", "Incorrect k1");
        return;
    }

    isOk = false;
    ms.k2 = ui->Edit_k2->text().toDouble(&isOk);
    if (!isOk || ms.k2 <= 0 || ms.k2 > 100)
    {
        QMessageBox::critical(this, "Error", "Incorrect k2");
        return;
    }

    isOk = false;
    ms.k3 = ui->Edit_k3->text().toDouble(&isOk);
    if (!isOk || ms.k3 <= 0 || ms.k3 > 100)
    {
        QMessageBox::critical(this, "Error", "Incorrect k3");
        return;
    }

    isOk = false;
    ms.k4 = ui->Edit_k4->text().toDouble(&isOk);
    if (!isOk || ms.k4 <= 0 || ms.k4 > 100)
    {
        QMessageBox::critical(this, "Error", "Incorrect k4");
        return;
    }

    isOk = false;
    ms.k5 = ui->Edit_k5->text().toDouble(&isOk);
    if (!isOk || ms.k5 <= 0 || ms.k5 > 100)
    {
        QMessageBox::critical(this, "Error", "Incorrect k5");
        return;
    }

    isOk = false;
    ms.k6 = ui->Edit_k6->text().toDouble(&isOk);
    if (!isOk || ms.k6 <= 0 || ms.k6 > 100)
    {
        QMessageBox::critical(this, "Error", "Incorrect k6");
        return;
    }

    std::string strPos = ui->EditCoords->text().toStdString();
    float x, y, z;
//    sscanf(strPos.c_str(), "%f%f%f", &x, &y, &z);

    std::stringstream ss(strPos);
    ss >> x >> y >> z;
    ms.BodyStartPos = {x, y, z};

    wgtDrawGL->InitPhysics(ms);
    TimerMain.stop();
    TimerMain.start(1000/60 - 1, this);
}
//-------------------------------------------------------------

void MainWindow::timerEvent(QTimerEvent *event)
{
    wgtDrawGL->NextStep(Basic_dt/1e3);
    (void)event;
}
//-------------------------------------------------------------
