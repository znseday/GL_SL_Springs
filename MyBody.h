#ifndef MYBODY_H
#define MYBODY_H

#include "MyTypes.h"
#include "MySphere.h"

#include <QOpenGLFunctions>
//#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

struct MaterialInfo
{
    QVector3D Ka{0.2, 0.2, 0.2};
    QVector3D Kd{0.8, 0.8, 0.8};
    QVector3D Ks{0.9, 0.9, 0.9};
    float Shininess = 10.0;
};

class MyBody : public IDrawableIn3D, public MySphere, protected QOpenGLFunctions
{
private:
    Pos3d CenterPos;

    double m = 1.0;

    QVector3D V;
    QVector3D a;

    const QMatrix4x4 &ProjMatrix;

    MaterialInfo Material;

    QOpenGLBuffer BufferBodyVerticies;
    QOpenGLBuffer BufferBodyIndecies;

public:
    MyBody(QMatrix4x4 &_projMatrix);
    ~MyBody();

//    void AddDataToShader(QOpenGLShaderProgram *program);

    void SetPos(const Pos3d &_center) {CenterPos = _center;}
    const Pos3d & GetPos() const {return CenterPos;}

    void Set_m(double _m) {m = _m;}

    void NextStep(double dt, const QVector3D &_F);

    void DrawIn3D(QMatrix4x4 mvMatrix, QOpenGLShaderProgram *program) override;

    void Reset_v_a() {V = a = {} /*QVector3D(0, 0, 0)*/;}
};

#endif // MYBODY_H
