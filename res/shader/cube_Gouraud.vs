#version 410 core

attribute vec3 vPos;
attribute vec2 vTexCoord;
attribute vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 vLightingColor;
uniform vec3 vLightPos;
uniform vec3 vViewPos;

out vec3 Normal;
out vec3 FragPos;
out vec4 LightingColor;
out vec3 LightPos;
out vec3 ViewPos;

void main()
{
    gl_Position = projection * view * model * vec4(vPos, 1.0);
    // Normal = mat3(transpose(inverse(model))) * vNormal;
    // FragPos = vec3(model * vec4(vPos, 1.0));

    // gouraud shading
    // ------------------------
    vec3 Position = vec3(model * vec4(vPos, 1.0));
    vec3 Normal = mat3(transpose(inverse(model))) * vNormal;
    
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vLightingColor.xyz;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(vLightPos - Position);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vLightingColor.xyz;
    
    // specular
    float specularStrength = 1.0; // this is set higher to better show the effect of Gouraud shading 
    vec3 viewDir = normalize(vViewPos - Position);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * vLightingColor.xyz;      

    LightingColor = vec4(ambient + diffuse + specular, 1.0);
}