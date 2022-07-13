#version 410 core

attribute vec3 vPos;
attribute vec2 vTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 outColor;

void main()
{
    gl_Position = projection * view * model * vec4(vPos, 1.0);
}