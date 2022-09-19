#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QOpenGLShaderProgram>
//#include <QOpenGLTexture>

class MySpringModel;

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
private:
    MySpringModel *SpringModel = nullptr;
    QVector2D OldXY, CurXY;
    QVector3D RotationAxis;
    QVector3D Trans;
    QQuaternion RotationQuaternion;
    float Angle = 0.0f;

    QMatrix4x4 ProjMatrix;
    QMatrix4x4 RotMatrix;

//    void InitShaders();
    void PintInfo();

    int FrameNumber = 0;

public:
    explicit MyOpenGLWidget(/*MySpringModel &_sptingModel,*/ QWidget *parent = nullptr);

    ~MyOpenGLWidget();

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    // QOpenGLWidget interface
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

};

#endif // MYOPENGLWIDGET_H
