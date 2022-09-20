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
//-------------------------------------------------------------


MyWorldBounds::MyWorldBounds(QMatrix4x4 &_projMatrix)
    : ProjMatrix(_projMatrix)
{
    this->initializeOpenGLFunctions();
}
//-------------------------------------------------------------

void MyWorldBounds::DrawIn3D(QMatrix4x4 mvMatrix, QOpenGLShaderProgram *program)
{
    program->setUniformValue("mvp_matrix", ProjMatrix * mvMatrix);
    program->setUniformValue("OneColor", QVector3D(0.5, 0.5, 0.5));

    constexpr GLint vPositionAttr = 0;

    glVertexAttribPointer(vPositionAttr, 3, GL_FLOAT, GL_FALSE, 0, WorldVerticesLineLoop1);
    glEnableVertexAttribArray(vPositionAttr);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
//    glDisableVertexAttribArray(vPositionAttr);  // Нужно ли?

    glVertexAttribPointer(vPositionAttr, 3, GL_FLOAT, GL_FALSE, 0, WorldVerticesLineLoop2);
//    glEnableVertexAttribArray(vPositionAttr);  // Нужно ли?
    glDrawArrays(GL_LINE_LOOP, 0, 4);
//    glDisableVertexAttribArray(vPositionAttr);  // Нужно ли?

    glVertexAttribPointer(vPositionAttr, 3, GL_FLOAT, GL_FALSE, 0, WorldVerticesLines);
//    glEnableVertexAttribArray(vPositionAttr);  // Нужно ли?
    glDrawArrays(GL_LINES, 0, 8);
//    glDisableVertexAttribArray(vPositionAttr); // Нужно ли?

    glVertexAttribPointer(vPositionAttr, 3, GL_FLOAT, GL_FALSE, 0, WorldVerticesCrossLineLoops);
//    glEnableVertexAttribArray(vPositionAttr);  // Нужно ли?
    for (int i = 0; i < 3; ++i)
        glDrawArrays(GL_LINE_LOOP, i*4, 4);

    glDisableVertexAttribArray(vPositionAttr);  // Нужно ли?
}
//-------------------------------------------------------------
