#include "MyBodyTrace.h"

#include <QOpenGLShaderProgram>


MyBodyTrace::MyBodyTrace(QMatrix4x4 &_projMatrix)
    : ProjMatrix(_projMatrix)
{
    this->initializeOpenGLFunctions();

//    TraceVertices.resize(MaxTraceVertices*3);

    BufferTraceVertices.create();
    BufferTraceVertices.bind();                 // StaticDraw !!!!!!!!!
//    BufferTraceVertices.setUsagePattern(QOpenGLBuffer::StaticDraw);
    BufferTraceVertices.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    BufferTraceVertices.allocate(TraceVertices.data(), TraceVertices.size()*sizeof(float));

}
//-------------------------------------------------------------

MyBodyTrace::~MyBodyTrace()
{
    BufferTraceVertices.release();
    BufferTraceVertices.destroy();
}
//-------------------------------------------------------------

void MyBodyTrace::AddPoint(const Pos3d &_vPos)
{
//    qDebug() << _vPos;

    TraceList.emplace_back(_vPos);
    if (TraceList.size() > MaxTraceVertices)
        TraceList.pop_front();


    size_t i = 0;
    for (const auto & item : TraceList)
    //for (auto it = TraceList.cbegin(); it != TraceList.cend(); ++it)
    {
//        auto item = *it;

        TraceVertices[i++] = item.x();
        TraceVertices[i++] = item.y();
        TraceVertices[i++] = item.z();

//        i += 3;
    }

    BufferTraceVertices.bind();
    BufferTraceVertices.write(0, TraceVertices.data(), TraceList.size()*sizeof(Pos3d));
    BufferTraceVertices.release();
}
//-------------------------------------------------------------

void MyBodyTrace::DrawIn3D(QMatrix4x4 mvMatrix, QOpenGLShaderProgram *program)
{
//    size_t i = 0;
//    for (const auto & item : TraceList)
//    {
//        TraceVertices[i+0] = item.x();
//        TraceVertices[i+1] = item.y();
//        TraceVertices[i+2] = item.z();

//        i += 3;
//    }

//    BufferTraceVertices.bind();
//    BufferTraceVertices.write(0, TraceVertices.data(), TraceList.size()*sizeof(Pos3d));
//    BufferTraceVertices.release();

    constexpr GLint vPositionAttr = 0;

    BufferTraceVertices.bind(); // v v v

    program->setUniformValue("mvp_matrix", ProjMatrix * mvMatrix);

    program->enableAttributeArray(vPositionAttr);

    program->setAttributeBuffer(vPositionAttr, GL_FLOAT, 0, 3, 0);

    glDrawArrays(GL_LINE_STRIP, 0, TraceList.size());

    BufferTraceVertices.release();

    program->disableAttributeArray(vPositionAttr);
}
