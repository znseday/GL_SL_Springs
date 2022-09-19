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

MySpringModel::MySpringModel()
{
    this->initializeOpenGLFunctions();

    WorldBounds = new MyWorldBounds(ProjMatrix);
    Body = new MyBody(ProjMatrix);
}

MySpringModel::~MySpringModel()
{
    delete WorldBounds;
    delete Body;

//    ProgramAnyColor.release(); // ?
//    ProgramOneColor.release(); // ?
//    ProgramADSColor.release(); // ?
}

void MySpringModel::InitPhysics(const PhyModelSettings &ms)
{

    (void)ms;
}

void MySpringModel::NextStep(double dt)
{

    (void)dt;
}

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

void MySpringModel::DrawIn3D(QMatrix4x4 mvMatrix, QOpenGLShaderProgram *program)
{   
    (void)program;

    if (!ProgramAnyColor.bind())  // Bind shader pipeline for use
    {
        qCritical() << "ProgramAnyColor.bind() Failed!";
        return;
    }

    ProgramAnyColor.setUniformValue("mvp_matrix", ProjMatrix * mvMatrix);
    MyDrawAxis();
    TestTriangle.DrawIn3D(mvMatrix, &ProgramAnyColor);


    if (!ProgramOneColor.bind())  // Bind shader pipeline for use
    {
        qCritical() << "ProgramOneColor.bind() Failed!";
        return;
    }
    WorldBounds->DrawIn3D(mvMatrix, &ProgramOneColor);

    if (!ProgramADSColor.bind())  // Bind shader pipeline for use
    {
        qCritical() << "ProgramADSColor.bind() Failed!";
        return;
    }

    ProgramADSColor.setUniformValue("Light.Position", mvMatrix*Light.Position);
    ProgramADSColor.setUniformValue("Light.La", Light.La);
    ProgramADSColor.setUniformValue("Light.Ld", Light.Ld);
    ProgramADSColor.setUniformValue("Light.Ls", Light.Ls);

    Body->DrawIn3D(mvMatrix, &ProgramADSColor);
}

