#ifndef MYSPRINGMODEL_H
#define MYSPRINGMODEL_H

#include "MyTypes.h"
#include "MyTestTriangle.h"
#include "MyWorldBounds.h"
#include "MyBody.h"
#include "MySpring.h"
#include "MyBodyTrace.h"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>



struct LightInfo
{
    QVector4D Position{10, 10, 10, 0}; // 3d vs 4d??? Позиция источника света в видимых координатах
    QVector3D La{0.2, 0.2, 0.2};
    QVector3D Ld{0.7, 0.7, 0.7};
    QVector3D Ls{0.5, 0.5, 0.5};
};

class MySpringModel : public IDrawableIn3D, protected QOpenGLFunctions
{
private:

    MyBody Body;
//    MySpring *SpringX1, *SpringX2,
//             *SpringY1, *SpringY2,
//             *SpringZ1, *SpringZ2;

    MySpring SpringX1, SpringX2,
             SpringY1, SpringY2,
             SpringZ1, SpringZ2;

    MyBodyTrace BodyTrace;

//    std::list<Pos3d> TraceList;
//    std::vector<float> TraceVertices;
//    QOpenGLBuffer BufferTraceVertices;

    MyTestTriangle TestTriangle;
    MyWorldBounds WorldBounds;

    QMatrix4x4 ProjMatrix;

    QOpenGLShaderProgram ProgramAnyColor;
    QOpenGLShaderProgram ProgramOneColor;
    QOpenGLShaderProgram ProgramADSColor;

    LightInfo Light;

    void MyDrawAxis();

public:
    MySpringModel();
    ~MySpringModel();

    void InitPhysics(const PhyModelSettings &ms);
    void NextStep(double dt);

    void InitProjMatrix(const QMatrix4x4 &_projMatrix) {ProjMatrix = _projMatrix;}
    void InitShaders();



    // IDrawableIn3D interface
public:
    void DrawIn3D(QMatrix4x4 mvMatrix, QOpenGLShaderProgram *program) override;
};

#endif // MYSPRINGMODEL_H
