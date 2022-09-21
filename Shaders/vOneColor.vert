#version 430

layout (location = 0) in vec3 VertexPosition;

uniform highp mat4 mvp_matrix;

void main()
{
    gl_Position = mvp_matrix * vec4(VertexPosition, 1.0);
}
