#include "MySpring.h"

QOpenGLBuffer MySpring::BufferVAO;

MySpring::MySpring(double _k, const Pos3d &_fixture)
    : k(_k), Fixture(_fixture)
{
    this->initializeOpenGLFunctions();
}
//-------------------------------------------------------------

MySpring::~MySpring()
{
}
//-------------------------------------------------------------

void MySpring::InitBufferVAO() // static
{
    std::vector<float> vertices; // x y z

    constexpr int n = 201;
    const double dh = BasicLen / (n-1);

    for (int i = 0; i < n; ++i)
    {
        double z = i*dh; //  [0 .. BasicLen]
        double fi = z*100;
        double x = Radius*cos(fi);
        double y = Radius*sin(fi);

        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
    }

    BufferVAO.create();
    BufferVAO.bind();
    BufferVAO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    BufferVAO.allocate(vertices.data(), vertices.size()*sizeof(float));

}
//-------------------------------------------------------------

void MySpring::DestroyBufferVAO() // static
{
    BufferVAO.release();
    BufferVAO.destroy();
}
//-------------------------------------------------------------

QVector3D MySpring::CalcF(const Pos3d &_end)
{
    ToEnd = _end; // здесь _end - это центр шарика

    QVector3D dir = Fixture - ToEnd; // в противоположную сторону (специально)
    double d = dir.length() / BasicLen - 1.0; // на сколько сжали или разжали (в долях)

    dir.normalize(); // делаем вектор единичным (нас интересует сейчас только направление)

    return dir*k*d;
}
//-------------------------------------------------------------

void MySpring::DrawIn3D(QMatrix4x4 mvMatrix, QOpenGLShaderProgram *program)
{
//    glLineWidth(2.0f);

//    glPushMatrix();

//    QVector3D a = ToEnd - Fixture;
//    double scale_z = a.length() / BasicLen;

//    double theta = acos(a.z() / a.length()) * 180.0 / M_PI;
//    double fi;
//    if ( qFuzzyCompare(a.toVector2D().length(), 0) )
//        fi = 0;
//    else
//        fi = acos(a.y() / a.toVector2D().length()) * 180.0 / M_PI;

//    glTranslatef(Fixture.x(), Fixture.y(), Fixture.z());  // 4 step
//    glRotatef( (a.x() > 0) ? -fi : fi, 0, 0, 1);          // 3 step
//    glRotatef(-theta, 1, 0, 0);                           // 2 step

//    glScalef(1, 1, scale_z);                              // 1 step

//    DrawBasicSpring();

//    glPopMatrix();
}
//-------------------------------------------------------------
