#version 410 core

out vec4 FragColor;

uniform vec4 vColor;
uniform vec3 vLightPos;
uniform vec4 vLightingColor;
uniform vec3 vViewPos;

in vec3 Normal;
in vec3 FragPos;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vLightingColor.xyz;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(vLightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vLightingColor.xyz;
    // vec3 diffuse = vec3(0.0);

    float specularStrength = 0.8;
    vec3 viewDir = normalize(vViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    vec3 specular = specularStrength * spec * vLightingColor.xyz;
    // vec3 specular = vec3(0.0);

    vec4 result = vec4(ambient + diffuse + specular, 1.0) * vColor;
    // FragColor = vec4(Normal, 1.0);
    FragColor = result;
} 
