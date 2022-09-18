#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBasicTimer>

#include "MySpringModel.h"

class MyOpenGLWidget;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;

    QBasicTimer TimerMain;

//    MySpringModel *SpringModel;
    MyOpenGLWidget *wgtDrawGL;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionFile_Exit_triggered();


};
#endif // MAINWINDOW_H
