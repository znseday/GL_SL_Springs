#include "MySpring.h"

#include <QOpenGLShaderProgram>

QOpenGLBuffer MySpring::BufferSpringVertices;

constexpr int nVertices = 601+2;

double MySpring::BasicLen = 1.0; // static

MySpring::MySpring(QMatrix4x4 &_projMatrix, const float &_bodyR)
    : ProjMatrix(_projMatrix), BodyRadius(_bodyR)
{
    this->initializeOpenGLFunctions();
}
//-------------------------------------------------------------

//MySpring::MySpring(double _k, const Pos3d &_fixture)
//    : k(_k), Fixture(_fixture)
//{
//    this->initializeOpenGLFunctions();
//}
//-------------------------------------------------------------

MySpring::~MySpring()
{
}
//-------------------------------------------------------------

void MySpring::InitBufferSpringVertices() // static
{
    std::vector<float> vertices; // x y z

    const double dh = BasicLen / (nVertices-1-2);

    vertices.push_back(0); vertices.push_back(0); vertices.push_back(0);

    for (int i = 0; i < nVertices-2; ++i)
    {
        double z = i*dh; //  [0 .. BasicLen]
        double fi = z*100;
        double x = Radius*cos(fi);
        double y = Radius*sin(fi);

        vertices.push_back(x); vertices.push_back(y); vertices.push_back(z);
    }
    vertices.push_back(0); vertices.push_back(0); vertices.push_back(BasicLen);

    BufferSpringVertices.create();
    BufferSpringVertices.bind();
    BufferSpringVertices.setUsagePattern(QOpenGLBuffer::StaticDraw);
    BufferSpringVertices.allocate(vertices.data(), vertices.size()*sizeof(float));

}
//-------------------------------------------------------------

void MySpring::DestroyBufferSpringVertices() // static
{
    BufferSpringVertices.release();
    BufferSpringVertices.destroy();
}
//-------------------------------------------------------------

QVector3D MySpring::CalcF(const Pos3d &_end)
{
    ToEnd = _end; // здесь _end - это центр шарика

    QVector3D dir = Fixture - ToEnd; // в противоположную сторону (специально)
    double d = (dir.length() - BodyRadius) - (BasicLen - BodyRadius); // на сколько сжали или разжали

    dir.normalize(); // делаем вектор единичным (нас интересует сейчас только направление)

    return dir*k*d;
}
//-------------------------------------------------------------

void MySpring::DrawIn3D(QMatrix4x4 mvMatrix, QOpenGLShaderProgram *program)
{
//    qDebug() << "BEFORE: " << mvMatrix;
    QVector3D a = ToEnd - Fixture;
    double scale_z = (a.length() - BodyRadius) / BasicLen;

    double theta = acos(a.z() / a.length()) * 180.0 / M_PI;
    double fi;
    if ( qFuzzyCompare(a.toVector2D().length(), 0) )
        fi = 0;
    else
        fi = acos(a.y() / a.toVector2D().length()) * 180.0 / M_PI;


    mvMatrix.translate(Fixture.x(), Fixture.y(), Fixture.z());  // 4 step 

    mvMatrix.rotate((a.x() > 0) ? -fi : fi, 0, 0, 1);           // 3 step
    mvMatrix.rotate(-theta, 1, 0, 0);                           // 2 step

    mvMatrix.scale(1, 1, scale_z);                              // 1 step

//    qDebug() << "AFTER: " << mvMatrix;

    constexpr GLint vPositionAttr = 0;

    BufferSpringVertices.bind(); // v v v

    program->setUniformValue("mvp_matrix", ProjMatrix * mvMatrix);

    program->enableAttributeArray(vPositionAttr);

    program->setAttributeBuffer(vPositionAttr, GL_FLOAT, 0, 3, 0);

    glDrawArrays(GL_LINE_STRIP, 0, nVertices);

    BufferSpringVertices.release();

    program->disableAttributeArray(vPositionAttr);

}
//-------------------------------------------------------------
