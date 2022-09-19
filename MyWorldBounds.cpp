#include "MyWorldBounds.h"

#include <QOpenGLShaderProgram>

static constexpr GLfloat WorldVerticesLineLoop1[] =
{
     -1.0f, -1.0f, -1.0f,
     -1.0f, -1.0f,  1.0f,
     -1.0f,  1.0f,  1.0f,
     -1.0f,  1.0f, -1.0f,
};

static constexpr GLfloat WorldVerticesLineLoop2[] =
{
      1.0f, -1.0f, -1.0f,
      1.0f, -1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,
      1.0f,  1.0f, -1.0f,
};

static constexpr GLfloat WorldVerticesLines[] =
{
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,
     1.0f, -1.0f, 1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,

    -1.0f,  1.0f, 1.0f,
     1.0f,  1.0f, 1.0f
};

//static constexpr GLfloat WorldVerticesCrossLineLoop1[] =
//{
//    -1.0f, -1.0f,  0.0f,
//    -1.0f,  1.0f,  0.0f,
//     1.0f,  1.0f,  0.0f,
//     1.0f, -1.0f,  0.0f
//};

//static constexpr GLfloat WorldVerticesCrossLineLoop2[] =
//{
//    0.0f, -1.0f, -1.0f,
//    0.0f,  1.0f, -1.0f,
//    0.0f,  1.0f,  1.0f,
//    0.0f, -1.0f,  1.0f
//};

//static constexpr GLfloat WorldVerticesCrossLineLoop3[] =
//{
//    -1.0f,  0.0f, -1.0f,
//     1.0f,  0.0f, -1.0f,
//     1.0f,  0.0f,  1.0f,
//    -1.0f,  0.0f,  1.0f
//};

static constexpr GLfloat WorldVerticesCrossLineLoops[] =
{
    -1.0f, -1.0f,  0.0f,
    -1.0f,  1.0f,  0.0f,
     1.0f,  1.0f,  0.0f,
     1.0f, -1.0f,  0.0f,

     0.0f, -1.0f, -1.0f,
     0.0f,  1.0f, -1.0f,
     0.0f,  1.0f,  1.0f,
     0.0f, -1.0f,  1.0f,

    -1.0f,  0.0f, -1.0f,
     1.0f,  0.0f, -1.0f,
     1.0f,  0.0f,  1.0f,
    -1.0f,  0.0f,  1.0f
};


MyWorldBounds::MyWorldBounds(QMatrix4x4 &_projMatrix)
    : ProjMatrix(_projMatrix)
{
    this->initializeOpenGLFunctions();
}

void MyWorldBounds::DrawIn3D(QMatrix4x4 mvMatrix, QOpenGLShaderProgram *program)
{
    program->setUniformValue("mvp_matrix", ProjMatrix * mvMatrix);

    GLint m_posAttr = 0;

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, WorldVerticesLineLoop1);
    glEnableVertexAttribArray(m_posAttr);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
//    glDisableVertexAttribArray(m_posAttr);  // Нужно ли?

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, WorldVerticesLineLoop2);
//    glEnableVertexAttribArray(m_posAttr);  // Нужно ли?
    glDrawArrays(GL_LINE_LOOP, 0, 4);
//    glDisableVertexAttribArray(m_posAttr);  // Нужно ли?

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, WorldVerticesLines);
//    glEnableVertexAttribArray(m_posAttr);  // Нужно ли?
    glDrawArrays(GL_LINES, 0, 8);
//    glDisableVertexAttribArray(m_posAttr); // Нужно ли?

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, WorldVerticesCrossLineLoops);
//    glEnableVertexAttribArray(m_posAttr);
    for (int i = 0; i < 3; ++i)
        glDrawArrays(GL_LINE_LOOP, i*4, 4);

    glDisableVertexAttribArray(m_posAttr);  // Нужно ли?
}
