#version 410 core

out vec4 FragColor;

uniform vec4 vColor;

in vec3 Normal;
in vec3 FragPos;
in vec4 LightingColor;

void main()
{
    FragColor = LightingColor * vColor;
} 
