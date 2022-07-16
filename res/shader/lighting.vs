#version 410 core

attribute vec3 vPos;
attribute vec2 vTexCoord;

uniform mat4 model = mat4(1.0f);
uniform mat4 view = mat4(1.0f);
uniform mat4 projection = mat4(1.0f);

void main()
{
    gl_Position = projection * view * model * vec4(vPos, 1.0);
}