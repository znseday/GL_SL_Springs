#ifndef MYTESTTRIANGLE_H
#define MYTESTTRIANGLE_H

#include "MyTypes.h"

#include <QOpenGLFunctions>

class MyTestTriangle : public IDrawableIn3D, protected QOpenGLFunctions
{
public:
    MyTestTriangle();

    // IDrawableIn3D interface
public:
    void DrawIn3D(QMatrix4x4 mvMatrix, QOpenGLShaderProgram *program) override;
};

#endif // MYTESTTRIANGLE_H
