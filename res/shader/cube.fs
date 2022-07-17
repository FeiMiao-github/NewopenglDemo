#version 410 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

uniform vec3 vViewPos;
uniform Material vMaterial;
uniform Light vLight;

in vec3 Normal;
in vec3 FragPos;

void main()
{
    vec3 ambient =  vLight.ambient * vMaterial.ambient;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(vLight.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = vLight.diffuse * (diff * vMaterial.diffuse);

    float specularStrength = 0.8;
    vec3 viewDir = normalize(vViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), vMaterial.shininess);
    vec3 specular = vLight.specular * (spec * vMaterial.specular);

    vec4 result = vec4(ambient + diffuse + specular, 1.0);
    FragColor = result;
} 
