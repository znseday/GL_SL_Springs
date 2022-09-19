#include "MyTestTriangle.h"

#include <QOpenGLShaderProgram>

static constexpr GLfloat vertices[] =
{
     0.0f,  0.707f,
    -0.5f, -0.5f,
     0.5f, -0.5f
};

static constexpr GLfloat colors[] =
{
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};


MyTestTriangle::MyTestTriangle()
{
    this->initializeOpenGLFunctions();
}

void MyTestTriangle::DrawIn3D(QMatrix4x4 mvMatrix, QOpenGLShaderProgram *_program)
{
    (void)mvMatrix;

    constexpr GLint vPositionAttr = 0;
    constexpr GLint vColorAttr = 1;

    glVertexAttribPointer(vPositionAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(vColorAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

    glEnableVertexAttribArray(vPositionAttr);
    glEnableVertexAttribArray(vColorAttr);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(vPositionAttr);
    glDisableVertexAttribArray(vColorAttr);

    (void)_program;
}
