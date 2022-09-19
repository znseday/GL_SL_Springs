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

void MySpringModel::MyDrawAxis() const
{

}

MySpringModel::MySpringModel()
{
    this->initializeOpenGLFunctions();

    WorldBounds = new MyWorldBounds(ProjMatrix);
}

MySpringModel::~MySpringModel()
{
    delete WorldBounds;
}

void MySpringModel::InitPhysics(const ModelSettings &ms)
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
        qCritical() << "addShaderFromSourceFile (Vertex) Failed!";
        return;
    }

    if (!ProgramAnyColor.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/fAnyColor.frag"))
    {
        qCritical() << "addShaderFromSourceFile (Fragment) Failed!";
        return;
    }

    if (!ProgramAnyColor.link())  // Link shader pipeline
    {
        qCritical() << "ProgramAnyColor.link() Failed!";
        return;
    }

    if (!ProgramOneColor.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/vOneColor.vert"))
    {
        qCritical() << "addShaderFromSourceFile (Vertex) Failed!";
        return;
    }

    if (!ProgramOneColor.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/fOneColor.frag"))
    {
        qCritical() << "addShaderFromSourceFile (Fragment) Failed!";
        return;
    }

    if (!ProgramOneColor.link())  // Link shader pipeline
    {
        qCritical() << "ProgramOneColor.link() Failed!";
        return;
    }

//    if (!ProgramBasic.bind())  // Bind shader pipeline for use
//    {
//        qCritical() << "ProgramBasic.bind() Failed!";
//        return;
//    }
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

    GLint m_posAttr = 0;
    GLint m_colAttr = 1;

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, AxisVertices);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, Axiscolors);

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    glDrawArrays(GL_LINES, 0, 6);

    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);

    TestTriangle.DrawIn3D(mvMatrix, &ProgramAnyColor);

    if (!ProgramOneColor.bind())  // Bind shader pipeline for use
    {
        qCritical() << "ProgramOneColor.bind() Failed!";
        return;
    }

    WorldBounds->DrawIn3D(mvMatrix, &ProgramOneColor);
}

