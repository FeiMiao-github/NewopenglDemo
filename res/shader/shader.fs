#version 410 core

out vec4 FragColor;

in vec3 voutColor;
in vec2 voutTexcoord;

void main()
{
    FragColor = vec4(voutColor.xyz, 1.0);
} 
