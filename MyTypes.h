#ifndef MYTYPES_H
#define MYTYPES_H

#include <QVector3D>

using Pos3d = QVector3D;

class QOpenGLShaderProgram;

class IDrawableIn3D
{
public:
    virtual void DrawIn3D(QOpenGLShaderProgram *program) = 0;
    virtual ~IDrawableIn3D() = default;
};


#endif // MYTYPES_H
