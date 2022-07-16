#version 410 core

out vec4 FragColor;

uniform vec4 vLightingColor;
uniform vec4 vColor;

void main()
{
    FragColor = vColor * vLightingColor;
} 
