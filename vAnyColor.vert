#version 430

in vec4 VertexPosition;
in vec3 VertexColor;

out vec3 Color;

uniform highp mat4 mvp_matrix;

void main()
{
   Color = VertexColor;
   gl_Position = mvp_matrix * VertexPosition;
}
