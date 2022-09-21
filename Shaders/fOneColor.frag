#version 430

layout (location = 0) out vec4 FragColor;

uniform vec3 OneColor;

void main()
{
    FragColor = vec4(OneColor, 1.0);
};
