#ifndef DEMO_COLORDEF_H__
#define DEMO_COLORDEF_H__

#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace demo
{
    class Color
    {
    public:
        constexpr static glm::vec4 White = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        constexpr static glm::vec4 Black = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
        constexpr static glm::vec4 Coral = glm::vec4(1.0f, 0.5f, 0.31f, 1.0f);
    };
}

#endif