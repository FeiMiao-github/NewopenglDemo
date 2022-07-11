#version 410 core

out vec4 FragColor;

in vec3 voutColor;
in vec2 voutTexcoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, voutTexcoord);
} 
