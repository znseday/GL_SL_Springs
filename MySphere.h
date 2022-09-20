#ifndef MYSPHERE_H
#define MYSPHERE_H

#include <vector>

class MySphere
{
private:

    void AddVertex(float x, float y, float z);
    void AddNormal(float x, float y, float z);
    void AddTexCoord(float s, float t);
    void AddIndices(unsigned int i1, unsigned int i2, unsigned int i3);

    void BuildVerticesSmooth();
    void BuildInterleavedVertices();

protected:

    float Radius;
    int SectorCount;
    int StackCount;

    std::vector<float> Vertices;
    std::vector<float> Normals;
    std::vector<float> TexCoords;
    std::vector<unsigned> Indices;
    std::vector<unsigned> LineIndices;

    std::vector<float> InterleavedVertices;
    static constexpr int InterleavedStride = 32; // must be 32 bytes

public:
    MySphere(float _radius = 1.0f, int _sectorCount = 36, int _stackCount = 18);
    ~MySphere() = default;

    const float & GetRadius() const {return Radius;}
};


#endif
