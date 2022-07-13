#version 410 core

out vec4 FragColor;

uniform vec3 vLightingColor;
uniform vec3 vColor;

in vec3 outColor;
void main()
{
    FragColor = vec4(vColor, 1.0f) * vec4(vLightingColor, 1.0f);
} 
