#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexColor;

layout (location = 0) out vec3 Color;

uniform highp mat4 mvp_matrix;

void main()
{
    Color = VertexColor;
    gl_Position = mvp_matrix * vec4(VertexPosition, 1.0);
}
