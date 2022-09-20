#ifndef MYBODYTRACE_H
#define MYBODYTRACE_H

#include "MyTypes.h"

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

static constexpr int MaxTraceVertices = 500;

class MyBodyTrace : public IDrawableIn3D, protected QOpenGLFunctions
{
private:

    std::list<Pos3d> TraceList;
    std::array<float, MaxTraceVertices*3> TraceVertices;

    QOpenGLBuffer BufferTraceVertices;

    const QMatrix4x4 &ProjMatrix;

public:
    MyBodyTrace(QMatrix4x4 &_projMatrix);
    ~MyBodyTrace();

    void AddPoint(const Pos3d & _vPos);
    void ClearPoints() {TraceList.clear();}

    // IDrawableIn3D interface
public:
    void DrawIn3D(QMatrix4x4 mvMatrix, QOpenGLShaderProgram *program) override;
};

#endif // MYBODYTRACE_H
