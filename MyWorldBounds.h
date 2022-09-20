#ifndef MYWORLDBOUNDS_H
#define MYWORLDBOUNDS_H

#include "MyTypes.h"

#include <QOpenGLFunctions>

class MyWorldBounds : public IDrawableIn3D, protected QOpenGLFunctions
{
private:
    const QMatrix4x4 &ProjMatrix;

public:
    MyWorldBounds(QMatrix4x4 &_projMatrix);

    // IDrawableIn3D interface
public:
    void DrawIn3D(QMatrix4x4 mvMatrix, QOpenGLShaderProgram *program) override;
};

#endif // MYWORLDBOUNDS_H
