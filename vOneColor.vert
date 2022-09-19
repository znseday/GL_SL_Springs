#version 430

in vec4 VertexPosition;

uniform highp mat4 mvp_matrix;

void main()
{
   gl_Position = mvp_matrix * VertexPosition;
}
