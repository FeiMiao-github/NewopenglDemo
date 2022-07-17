#ifndef DEMO_MATERIAL_H__
#define DEMO_MATERIAL_H__

#include "glm/ext/vector_float3.hpp"

namespace demo
{
    struct Material
    {
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float shininess;

        const static Material test;
    };
};

#endif