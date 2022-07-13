#ifndef DEMO_COLORDEF_H__
#define DEMO_COLORDEF_H__

#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace demo
{
    class Color
    {
    public:
        constexpr static glm::vec3 Coral = glm::vec3(1.0f, 0.5f, 0.31f);
    };
}

#endif