#include "MySpringModel.h"

void MySpringModel::MyDrawAxis() const
{

}

void MySpringModel::InitPhysics(const ModelSettings &ms)
{

    (void)ms;
}

void MySpringModel::NextStep(double dt)
{

    (void)dt;
}

void MySpringModel::DrawIn3D(QOpenGLShaderProgram *program)
{
    TestTriangle.DrawIn3D(program);
}

