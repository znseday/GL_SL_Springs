#include "MySpringModel.h"

#include <QOpenGLShaderProgram>



static constexpr GLfloat AxisVertices[] =
{
     -1.0f,  0.0f,  0.0f,
      1.0f,  0.0f,  0.0f,
      0.0f, -1.0f,  0.0f,
      0.0f,  1.0f,  0.0f,
      0.0f,  0.0f, -1.0f,
      0.0f,  0.0f,  1.0f
};

static constexpr GLfloat Axiscolors[] =
{
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f
};
//-------------------------------------------------------------

void MySpringModel::MyDrawAxis()
{
    constexpr GLint vPositionAttr = 0;
    constexpr GLint vColorAttr = 1;

    glVertexAttribPointer(vPositionAttr, 3, GL_FLOAT, GL_FALSE, 0, AxisVertices);
    glVertexAttribPointer(vColorAttr, 3, GL_FLOAT, GL_FALSE, 0, Axiscolors);

    glEnableVertexAttribArray(vPositionAttr);
    glEnableVertexAttribArray(vColorAttr);

    glDrawArrays(GL_LINES, 0, 6);

    glDisableVertexAttribArray(vColorAttr);
    glDisableVertexAttribArray(vPositionAttr);
}
//-------------------------------------------------------------

MySpringModel::MySpringModel()
    : Body(ProjMatrix),
      SpringX1(ProjMatrix, Body.GetRadius()), SpringX2(ProjMatrix, Body.GetRadius()),
      SpringY1(ProjMatrix, Body.GetRadius()), SpringY2(ProjMatrix, Body.GetRadius()),
      SpringZ1(ProjMatrix, Body.GetRadius()), SpringZ2(ProjMatrix, Body.GetRadius()),
      BodyTrace(ProjMatrix),
      WorldBounds(ProjMatrix)
{
    this->initializeOpenGLFunctions();

    MySpring::SetBasicLen(1.0 - Body.GetRadius());
}
//-------------------------------------------------------------

MySpringModel::~MySpringModel()
{
//    BufferTraceVertices.release();
//    BufferTraceVertices.destroy();

//    ProgramAnyColor.release(); // ?
//    ProgramOneColor.release(); // ?
//    ProgramADSColor.release(); // ?
}
//-------------------------------------------------------------

void MySpringModel::InitPhysics(const PhyModelSettings &ms)
{
    BodyTrace.ClearPoints();
    Body.Set_m(ms.m);
//    Body->SetPos({0.4, -0.3, 0.5});
    Body.SetPos(ms.BodyStartPos);
    Body.Reset_v_a();

    SpringX1.SetFixture({-1,  0,  0});  SpringX1.Set_k(ms.k1);   //SpringX1.SetBasicLen(1.2);
    SpringX2.SetFixture({ 1,  0,  0});  SpringX2.Set_k(ms.k2);
    SpringY1.SetFixture({ 0, -1,  0});  SpringY1.Set_k(ms.k3);
    SpringY2.SetFixture({ 0,  1,  0});  SpringY2.Set_k(ms.k4);
    SpringZ1.SetFixture({ 0,  0, -1});  SpringZ1.Set_k(ms.k5);
    SpringZ2.SetFixture({ 0,  0,  1});  SpringZ2.Set_k(ms.k6);

    BodyTrace.AddPoint(Body.GetPos());
    NextStep(0);
}
//-------------------------------------------------------------

void MySpringModel::NextStep(double dt)
{
    static int n = 0;

    QVector3D F = SpringX1.CalcF(Body.GetPos()) +
                  SpringX2.CalcF(Body.GetPos()) +
                  SpringY1.CalcF(Body.GetPos()) +
                  SpringY2.CalcF(Body.GetPos()) +
                  SpringZ1.CalcF(Body.GetPos()) +
                  SpringZ2.CalcF(Body.GetPos());

    Body.NextStep(dt, F);

    if (++n % 3 == 0)
    {
        BodyTrace.AddPoint(Body.GetPos());
    }
}
//-------------------------------------------------------------

void MySpringModel::InitShaders()
{
    if (!ProgramAnyColor.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/vAnyColor.vert"))
    {
        qCritical() << "ProgramAnyColor.addShaderFromSourceFile (Vertex) Failed!";
        return;
    }

    if (!ProgramAnyColor.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/fAnyColor.frag"))
    {
        qCritical() << "ProgramAnyColor.addShaderFromSourceFile (Fragment) Failed!";
        return;
    }

    if (!ProgramAnyColor.link())  // Link shader pipeline
    {
        qCritical() << "ProgramAnyColor.link() Failed!";
        return;
    }
    //------------

    if (!ProgramOneColor.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/vOneColor.vert"))
    {
        qCritical() << "ProgramOneColor.addShaderFromSourceFile (Vertex) Failed!";
        return;
    }

    if (!ProgramOneColor.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/fOneColor.frag"))
    {
        qCritical() << "ProgramOneColor.addShaderFromSourceFile (Fragment) Failed!";
        return;
    }

    if (!ProgramOneColor.link())  // Link shader pipeline
    {
        qCritical() << "ProgramOneColor.link() Failed!";
        return;
    }
    //-----------

    if (!ProgramADSColor.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/vADSColor.vert"))
    {
        qCritical() << "ProgramADSColor.addShaderFromSourceFile (Vertex) Failed!";
        return;
    }

    if (!ProgramADSColor.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/fADSColor.frag"))
    {
        qCritical() << "ProgramADSColor.addShaderFromSourceFile (Fragment) Failed!";
        return;
    }

    if (!ProgramADSColor.link())  // Link shader pipeline
    {
        qCritical() << "ProgramADSColor.ProgramOneColor.link() Failed!";
        return;
    }
}
//-------------------------------------------------------------

void MySpringModel::DrawIn3D(QMatrix4x4 mvMatrix, QOpenGLShaderProgram *program)
{   
    (void)program;

    glLineWidth(1.0f);

    if (!ProgramAnyColor.bind())  // Bind shader pipeline for use
    {
        qCritical() << "ProgramAnyColor.bind() Failed!";
        return;
    }

    ProgramAnyColor.setUniformValue("mvp_matrix", ProjMatrix * mvMatrix);
    MyDrawAxis();
//    TestTriangle.DrawIn3D(mvMatrix, &ProgramAnyColor);
    //--------------

    if (!ProgramOneColor.bind())  // Bind shader pipeline for use
    {
        qCritical() << "ProgramOneColor.bind() Failed!";
        return;
    }
    WorldBounds.DrawIn3D(mvMatrix, &ProgramOneColor);

    ProgramOneColor.setUniformValue("OneColor", QVector3D(0.1, 0.6, 0.6));
    BodyTrace.DrawIn3D(mvMatrix, &ProgramOneColor);

    glLineWidth(2.0f);

    ProgramOneColor.setUniformValue("OneColor", QVector3D(0.9, 0.1, 0.1));
    SpringX1.DrawIn3D(/*ProjMatrix **/ mvMatrix, &ProgramOneColor);
    SpringX2.DrawIn3D(/*ProjMatrix **/ mvMatrix, &ProgramOneColor);

    ProgramOneColor.setUniformValue("OneColor", QVector3D(0.1, 0.9, 0.1));
    SpringY1.DrawIn3D(/*ProjMatrix **/ mvMatrix, &ProgramOneColor);
    SpringY2.DrawIn3D(/*ProjMatrix **/ mvMatrix, &ProgramOneColor);

    ProgramOneColor.setUniformValue("OneColor", QVector3D(0.1, 0.1, 0.9));
    SpringZ1.DrawIn3D(/*ProjMatrix **/ mvMatrix, &ProgramOneColor);
    SpringZ2.DrawIn3D(/*ProjMatrix **/ mvMatrix, &ProgramOneColor);

    //--------------

    if (!ProgramADSColor.bind())  // Bind shader pipeline for use
    {
        qCritical() << "ProgramADSColor.bind() Failed!";
        return;
    }

//    ProgramADSColor.setUniformValue("Light.Position", mvMatrix*Light.Position);
    ProgramADSColor.setUniformValue("Light.Position", Light.Position);

    ProgramADSColor.setUniformValue("Light.La", Light.La);
    ProgramADSColor.setUniformValue("Light.Ld", Light.Ld);
    ProgramADSColor.setUniformValue("Light.Ls", Light.Ls);

    Body.DrawIn3D(mvMatrix, &ProgramADSColor);
}
//-------------------------------------------------------------

