#version 410 core

attribute vec3 vPos;
attribute vec3 vColor;
attribute vec2 vTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 voutColor;
out vec2 voutTexcoord;

void main()
{
    gl_Position = projection * view * model * vec4(vPos, 1.0);
    voutColor = vColor;
    voutTexcoord = vTexCoord;
}