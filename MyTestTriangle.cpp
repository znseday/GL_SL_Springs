#include "MyTestTriangle.h"

#include <QOpenGLShaderProgram>

static constexpr GLfloat vertices[] = {
     0.0f,  0.707f,
    -0.5f, -0.5f,
     0.5f, -0.5f
};

static constexpr GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};


MyTestTriangle::MyTestTriangle()
{
    this->initializeOpenGLFunctions();
}

void MyTestTriangle::DrawIn3D(QOpenGLShaderProgram *_program)
{
    GLint m_posAttr = 0;
    GLint m_colAttr = 1;

    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);

    (void)_program;
}
