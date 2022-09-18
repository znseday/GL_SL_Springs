#ifndef MYSPRINGMODEL_H
#define MYSPRINGMODEL_H

#include "MyTypes.h"
#include "MyTestTriangle.h"

#include <QOpenGLFunctions>

struct ModelSettings
{
    Pos3d  BodyStartPos;
    double m = 1;
    double k1 = 1;
    double k2 = 1;
    double k3 = 1;
    double k4 = 1;
    double k5 = 1;
    double k6 = 1;
};

class MySpringModel : public IDrawableIn3D, protected QOpenGLFunctions
{
private:

//    MyBody Body;
//    MySpring SpringX1;
    MyTestTriangle TestTriangle;

    void MyDrawAxis() const;

public:
    MySpringModel() = default;

    void InitPhysics(const ModelSettings &ms);
    void NextStep(double dt);

    // IDrawableIn3D interface
public:
    void DrawIn3D(QOpenGLShaderProgram *program) override;
};

#endif // MYSPRINGMODEL_H
