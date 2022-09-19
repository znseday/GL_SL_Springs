#ifndef MYSPRINGMODEL_H
#define MYSPRINGMODEL_H

#include "MyTypes.h"
#include "MyTestTriangle.h"
#include "MyWorldBounds.h"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

struct ModelSettings
{
    Pos3d  BodyStartPos;
    double m = 1;
    double k1 = 1;
    double k2 = 1;
    double k3 = 1;
    double k4 = 1;
    double k5 = 1;
    double k6 = 1;
};

class MySpringModel : public IDrawableIn3D, protected QOpenGLFunctions
{
private:


//    MyBody Body;
//    MySpring SpringX1;
    MyTestTriangle TestTriangle;
    MyWorldBounds *WorldBounds;

    QMatrix4x4 ProjMatrix;

    QOpenGLShaderProgram ProgramAnyColor;
    QOpenGLShaderProgram ProgramOneColor;

    void MyDrawAxis() const;

public:
    MySpringModel();
    ~MySpringModel();

    void InitPhysics(const ModelSettings &ms);
    void NextStep(double dt);

    void InitProjMatrix(const QMatrix4x4 &_projMatrix) {ProjMatrix = _projMatrix;}
    void InitShaders();

    // IDrawableIn3D interface
public:
    void DrawIn3D(QMatrix4x4 mvMatrix, QOpenGLShaderProgram *program) override;
};

#endif // MYSPRINGMODEL_H
