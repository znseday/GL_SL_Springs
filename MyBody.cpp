#include "MyBody.h"

#include <QOpenGLShaderProgram>

MyBody::MyBody(QMatrix4x4 &_projMatrix)
    : MySphere(1.0, 128, 128), ProjMatrix(_projMatrix), BufferIndecies(QOpenGLBuffer::IndexBuffer)
{
    this->initializeOpenGLFunctions();

    // Create Buffer (Do not release until VAO is created)
    BufferVAO.create();
    BufferVAO.bind();
    BufferVAO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    BufferVAO.allocate(InterleavedVertices.data(), InterleavedVertices.size()*sizeof(float));

    BufferIndecies.create();
    BufferIndecies.bind();
    BufferIndecies.setUsagePattern(QOpenGLBuffer::StaticDraw);
    BufferIndecies.allocate(Indices.data(), Indices.size()*sizeof(unsigned));

    // Create Vertex Array Object
//    VAO.create();
//    VAO.bind();
}
//-------------------------------------------------------------

MyBody::~MyBody()
{
    // Release (unbind) all
//    VAO.release();
    BufferVAO.release();
    BufferIndecies.release();

//    VAO.destroy();
    BufferVAO.destroy();
    BufferIndecies.destroy();
}
//-------------------------------------------------------------

void MyBody::NextStep(double dt, const QVector3D &_F)
{
    a = _F/m; // 2й з-н Ньютона

    // попробовать потом добавить гравитацию
//    a = _F/m + QVector3D{0, 0, -9.8}; // 2й з-н Ньютона

//    CenterPos = CenterPos + V*dt + a*dt*dt/2.0; // Формула из кинематики для равноускоренного движения

    V = V + a*dt; // Формула из кинематики для равноускоренного движения

    CenterPos = CenterPos + V*dt; // Формула из кинематики для равномерного движения
}
//-------------------------------------------------------------

void MyBody::DrawIn3D(QMatrix4x4 mvMatrix, QOpenGLShaderProgram *program)
{
    mvMatrix.translate(CenterPos);
    mvMatrix.scale(0.1);
//    mvMatrix.scale(1.0, 0.2, 1.0);

//    program->setUniformValue("Material", Material);

    program->setUniformValue("Material.Ka", Material.Ka);
    program->setUniformValue("Material.Kd", Material.Kd);
    program->setUniformValue("Material.Ks", Material.Ks);
    program->setUniformValue("Material.Shininess", Material.Shininess);

    program->setUniformValue("mv_matrix", mvMatrix);

    QMatrix3x3 nMatrix = mvMatrix.toGenericMatrix<3, 3>();

    program->setUniformValue("n_matrix", nMatrix);

    program->setUniformValue("mvp_matrix", ProjMatrix * mvMatrix);

    constexpr GLint vPositionAttr = 0;
    constexpr GLint vNormalAttr = 1;
    constexpr GLint vTexAttr = 2;

    // v v v  n n n  t t
    BufferVAO.bind();
    BufferIndecies.bind();

    program->enableAttributeArray(vPositionAttr);
    program->enableAttributeArray(vNormalAttr);
    program->enableAttributeArray(vTexAttr);


    program->setAttributeBuffer(vPositionAttr, GL_FLOAT, 0, 3, InterleavedStride);
    program->setAttributeBuffer(vNormalAttr, GL_FLOAT, 3*sizeof(float), 3, InterleavedStride);
    program->setAttributeBuffer(vTexAttr, GL_FLOAT, (3+3)*sizeof(float), 2, InterleavedStride);

//    VAO.bind();
//    glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, Indices.data());
    glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, nullptr); // using BufferIndecies
//    VAO.release();

    BufferVAO.release();
    BufferIndecies.release();

    program->disableAttributeArray(vPositionAttr);
    program->disableAttributeArray(vNormalAttr);
    program->disableAttributeArray(vTexAttr);
}
//-------------------------------------------------------------



