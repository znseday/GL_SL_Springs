#ifndef MYSPRING_H
#define MYSPRING_H

#include "MyTypes.h"

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

class MySpring : public IDrawableIn3D, protected QOpenGLFunctions
{
private:

    double k = 1.0; // Н/м

    static constexpr double Radius = 0.035;
    static double BasicLen;

    Pos3d Fixture; // постоянное крепление к граням куба
    Pos3d ToEnd;   // точка крепления к шарику (на самом деле к центру шарика для упрощения)

    static QOpenGLBuffer BufferSpringVertices;

    const QMatrix4x4 &ProjMatrix;

    const float &BodyRadius;

public:
    MySpring(QMatrix4x4 &_projMatrix, const float &_bodyR);
//    MySpring(QMatrix4x4 &_projMatrix, double _k, const Pos3d &_fixture);

    ~MySpring();

    static void InitBufferSpringVertices();
    static void DestroyBufferSpringVertices();

    static void SetBasicLen(double _len) {BasicLen = _len;}

    void SetFixture(const Pos3d &_fixture) {Fixture = _fixture;}
    void Set_k(double _k) {k = _k;}

//    void SetBasicLen(double _bl) {BasicLen = _bl;}

//    void DrawBasicSpring() const;

    QVector3D CalcF(const Pos3d &_end);

    void DrawIn3D(QMatrix4x4 mvMatrix, QOpenGLShaderProgram *program) override;
};

#endif // MYSPRING_H
