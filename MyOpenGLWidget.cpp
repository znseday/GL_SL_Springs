#include "MyOpenGLWidget.h"
#include "MySpringModel.h"
#include "MySpring.h"

#include <QMouseEvent>
#include <QApplication>

static constexpr float cRot = 0.25f;
static constexpr float cTrans = 0.0025f;

void MyOpenGLWidget::PintInfo()
{
    auto renderer = glGetString(GL_RENDERER);
    qInfo() << "renderer =" << (const char*)renderer;

    auto vendor = glGetString(GL_VENDOR);
    qInfo() << "vendor =" << (const char*)vendor;

    auto version = glGetString(GL_VERSION);
    qInfo() << "version =" << (const char*)version;

    auto glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    qInfo() << "glslVersion =" << (const char*)glslVersion;

    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    qInfo() << "glslVersion (int, int) =" << major << "-" << minor;
}
//-------------------------------------------------------------

MyOpenGLWidget::MyOpenGLWidget(/*MySpringModel &_sptingModel,*/ QWidget *parent)
    : QOpenGLWidget(parent)/*, SpringModel(_sptingModel)*/
{
}
//-------------------------------------------------------------

MyOpenGLWidget::~MyOpenGLWidget()
{
    makeCurrent();
    delete SpringModel;
    MySpring::DestroyBufferVAO();
    doneCurrent();
}
//-------------------------------------------------------------

void MyOpenGLWidget::InitPhysics(const PhyModelSettings &ms)
{
    SpringModel->InitPhysics(ms);
}
//-------------------------------------------------------------

void MyOpenGLWidget::NextStep(double dt)
{
    SpringModel->NextStep(dt);
    this->update();
}
//-------------------------------------------------------------

void MyOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    OldXY = QVector2D(event->position());
}
//-------------------------------------------------------------

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    CurXY = QVector2D(event->position());
    QVector2D dXY = CurXY - OldXY;
    if (dXY.length() < 1)
        return;

    OldXY = CurXY;

    QVector3D n = QVector3D(dXY.y(), dXY.x(), 0.0).normalized();

    if (QApplication::keyboardModifiers() == Qt::AltModifier)
    {
        dXY.setY(-dXY.y());
        Trans += dXY.toVector3D() * cTrans;
//        TransX += cTrans*dx;
//        TransY -= cTrans*dy;
    }
    else if (QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
//        float dAngle = dXY.length() * cRot;
//        RotationQuaternion = QQuaternion::fromAxisAndAngle({0, 0, 1}, dAngle) * RotationQuaternion;

//        RotMatrix.setToIdentity();
//        RotMatrix.rotate(RotationQuaternion);
    }
    else
    {
        float dAngle = dXY.length() * cRot;

//        Angle += dAngle;

//        RotationAxis = (n * dAngle).normalized();

//        RotationQuaternion = QQuaternion::fromAxisAndAngle(RotationAxis, dAngle) /** RotationQuaternion*/;

//        RotMatrix.rotate(RotationQuaternion);

//        qreal acc = dXY.length() * cRot;

        // Calculate new rotation axis as weighted sum
//        RotationAxis = (RotationAxis * acc + n * acc).normalized();
        RotationAxis = (n).normalized();

        RotationQuaternion = QQuaternion::fromAxisAndAngle(RotationAxis, dAngle) * RotationQuaternion;

        RotMatrix.setToIdentity();
        RotMatrix.rotate(RotationQuaternion);
        // Increase angular speed
//        angularSpeed += acc;
    }

    this->update();     // Request an update
}
//-------------------------------------------------------------

void MyOpenGLWidget::wheelEvent(QWheelEvent *event)
{
    Trans += QVector3D(0, 0, event->angleDelta().y() / 700.0f);
    this->update();
}
//-------------------------------------------------------------

void MyOpenGLWidget::initializeGL()
{
    this->initializeOpenGLFunctions();

    PintInfo();

    SpringModel = new MySpringModel;

    MySpring::InitBufferVAO();

    RotMatrix.setToIdentity();
    SpringModel->InitShaders();

    SpringModel->InitPhysics(PhyModelSettings());

    glClearColor(0, 0, 0, 1);

//    InitShaders();

    glEnable(GL_DEPTH_TEST);
}
//-------------------------------------------------------------

void MyOpenGLWidget::resizeGL(int w, int h)
{
    double aspect = double(w) / double(h ? h : 1);

    const double zNear = 0.01, zFar = 20.0, fov = 45.0;

    ProjMatrix.setToIdentity();
    ProjMatrix.perspective(fov, aspect, zNear, zFar);

    SpringModel->InitProjMatrix(ProjMatrix);
}
//-------------------------------------------------------------

void MyOpenGLWidget::paintGL()
{
    ++FPS;
    tEndSecond = ClockType::now();

    double secTime = (double)std::chrono::duration_cast<std::chrono::milliseconds>(tEndSecond - tStartSecond).count();
    if (secTime >= 1000)
    {
        tStartSecond = ClockType::now();
        emit SignalSendCurrentFps(FPS);
        FPS = 0;
    }

//    qDebug() << __PRETTY_FUNCTION__ << "FrameNumber =" << FrameNumber++;
//    const qreal retinaScale = devicePixelRatio();
//    qDebug() << "retinaScale =" << retinaScale;
//    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -4.0);
//    qDebug() << matrix;
//    matrix.rotate(RotationQuaternion);

    QMatrix4x4 transMatrix;
    transMatrix.setToIdentity();
    transMatrix.translate(Trans);

    matrix *= transMatrix;
    matrix *= RotMatrix;

    SpringModel->DrawIn3D(matrix, nullptr);
}
//-------------------------------------------------------------
