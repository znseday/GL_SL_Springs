#ifndef MYTYPES_H
#define MYTYPES_H

#include <QVector3D>
#include <QMatrix4x4>

using Pos3d = QVector3D;

class QOpenGLShaderProgram;

struct PhyModelSettings
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

class IDrawableIn3D
{
public:
    virtual void DrawIn3D(QMatrix4x4 mvMatrix, QOpenGLShaderProgram *program) = 0;
    virtual ~IDrawableIn3D() = default;
};



#endif // MYTYPES_H
