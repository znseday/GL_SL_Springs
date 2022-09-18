#version 430

//varying lowp vec4 col;

//void main()
//{
//   gl_FragColor = col;
//};

//varying lowp vec4 col;

in vec3 Color;

layout (location = 0) out vec4 FragColor;

void main()
{
   FragColor = vec4(Color, 1.0);
};
