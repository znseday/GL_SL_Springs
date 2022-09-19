#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec3 VertexTex;

layout (location = 0) out vec3 LightIntensity;

struct LightInfo
{
    vec4 Position; // 3d vs 4d??? Позиция источника света в видимых координатах
    vec3 La;
    vec3 Ld;
    vec3 Ls;
};

uniform LightInfo Light;

struct MaterialInfo
{
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    float Shininess;
};

uniform MaterialInfo Material;
uniform mat4 mv_matrix;
uniform mat3 n_matrix;
//uniform mat4 p_matrix;
uniform mat4 mvp_matrix;

void main()
{
    vec3 tnorm = normalize(n_matrix*VertexNormal);
    vec4 eyeCoords = mv_matrix * vec4(VertexPosition, 1.0);

    vec3 s = normalize(vec3(Light.Position - eyeCoords));
    vec3 v = normalize(-eyeCoords.xyz);
    vec3 r = reflect(-s, tnorm);

    vec3 ambient = Light.La * Material.Ka;
    float sDotN = max(dot(s, tnorm), 0.0);
    vec3 diffuse = Light.Ld * Material.Kd * sDotN;
    vec3 spec = vec3(0.0);
    if (sDotN > 0)
        spec = Light.Ls * Material.Ks * pow(max(dot(r, v), 0.0), Material.Shininess);

    LightIntensity = ambient + diffuse + spec;

    gl_Position = mvp_matrix * vec4(VertexPosition, 1.0);
}
