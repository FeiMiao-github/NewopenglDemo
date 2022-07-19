#version 410 core

out vec4 FragColor;

struct Material
{
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 vViewPos;
uniform Material vMaterial;
uniform Light vLight;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

void main()
{
    vec3 ambient = vLight.ambient * vec3(texture(vMaterial.diffuse, TexCoords));

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(vLight.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = vLight.diffuse * diff * vec3(texture(vMaterial.diffuse, TexCoords));

    vec3 viewDir = normalize(vViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), vMaterial.shininess);
    vec3 specular = vLight.specular * (spec * vMaterial.specular);

    vec4 result = vec4(ambient + diffuse + specular, 1.0);
    FragColor = result;
} 
