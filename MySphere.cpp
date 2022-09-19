#include <cmath>
#include "MySphere.h"

constexpr int MinSectorCount = 3;
constexpr int MinStackCount  = 2;


MySphere::MySphere(float _radius, int _sectorCount, int _stackCount)
    : Radius(_radius), SectorCount(_sectorCount), StackCount(_stackCount)
{
    if (SectorCount < MinSectorCount)
        SectorCount = MinSectorCount;

    if (StackCount < MinStackCount)
        StackCount = MinStackCount;

    BuildVerticesSmooth();
}

// x = r * cos(u) * cos(v)
// y = r * cos(u) * sin(v)
// z = r * sin(u)
// u: stack(latitude) angle (-90 <= u <= 90)
// v: sector(longitude) angle (0 <= v <= 360)
void MySphere::BuildVerticesSmooth()
{
    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / Radius;    // normal
    float s, t;                                     // texCoord

    float sectorStep = 2 * M_PI / SectorCount;
    float stackStep = M_PI / StackCount;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= StackCount; ++i)
    {
        stackAngle = M_PI / 2 - i * stackStep;     // starting from pi/2 to -pi/2
        xy = Radius * cos(stackAngle);             // r * cos(u)
        z = Radius * sin(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for (int j = 0; j <= SectorCount; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position
            x = xy * cos(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sin(sectorAngle);             // r * cos(u) * sin(v)
            AddVertex(x, y, z);

            // normalized vertex normal
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            AddNormal(nx, ny, nz);

            // vertex tex coord between [0, 1]
            s = j / (float)SectorCount;
            t = i / (float)StackCount;
            AddTexCoord(s, t);
        }
    }

    // indices
    //  k1--k1+1
    //  |  / |
    //  | /  |
    //  k2--k2+1
    unsigned k1, k2;
    for (int i = 0; i < StackCount; ++i)
    {
        k1 = i * (SectorCount + 1);     // beginning of current stack
        k2 = k1 + SectorCount + 1;      // beginning of next stack

        for (int j = 0; j < SectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding 1st and last stacks
            if (i != 0)
            {
                AddIndices(k1, k2, k1+1);   // k1---k2---k1+1
            }

            if (i != (StackCount-1))
            {
                AddIndices(k1+1, k2, k2+1); // k1+1---k2---k2+1
            }

            // vertical lines for all stacks
            LineIndices.push_back(k1);
            LineIndices.push_back(k2);
            if (i != 0)  // horizontal lines except 1st stack
            {
                LineIndices.push_back(k1);
                LineIndices.push_back(k1 + 1);
            }
        }
    }

    // generate interleaved vertex array as well
    BuildInterleavedVertices();
}


void MySphere::BuildInterleavedVertices()
{
    size_t i, j;
    size_t count = Vertices.size();
    for (i = 0, j = 0; i < count; i += 3, j += 2)
    {
        InterleavedVertices.push_back(Vertices[i]);
        InterleavedVertices.push_back(Vertices[i+1]);
        InterleavedVertices.push_back(Vertices[i+2]);

        InterleavedVertices.push_back(Normals[i]);
        InterleavedVertices.push_back(Normals[i+1]);
        InterleavedVertices.push_back(Normals[i+2]);

        InterleavedVertices.push_back(TexCoords[j]);
        InterleavedVertices.push_back(TexCoords[j+1]);
    }
}


void MySphere::AddVertex(float x, float y, float z)
{
    Vertices.push_back(x); Vertices.push_back(y); Vertices.push_back(z);
}

void MySphere::AddNormal(float nx, float ny, float nz)
{
    Normals.push_back(nx); Normals.push_back(ny); Normals.push_back(nz);
}

void MySphere::AddTexCoord(float s, float t)
{
    TexCoords.push_back(s); TexCoords.push_back(t);
}

void MySphere::AddIndices(unsigned i1, unsigned i2, unsigned i3)
{
    Indices.push_back(i1); Indices.push_back(i2); Indices.push_back(i3);
}
