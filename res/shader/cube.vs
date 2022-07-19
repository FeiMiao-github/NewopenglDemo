#version 410 core

attribute vec3 vPos;
attribute vec2 vTexCoord;
attribute vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

void main()
{
    FragPos = vec3(model * vec4(vPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * vNormal; 
    TexCoords = vTexCoord;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}