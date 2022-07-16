#ifndef DEMO_SHAPE_H__
#define DEMO_SHAPE_H__

#include <cstddef>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace demo{
    class Cube
    {
    public:
        typedef struct {
            glm::vec3 pos;
            glm::vec2 texCoord;
            glm::vec3 abnormal;
        } PointData_t;

        typedef struct
        {
            GLuint index;
            GLint size;
            GLenum type;
            GLboolean normalized;
            GLsizei stride;
            void *pointer;
        } VertextAttr_t;

        Cube();
        virtual ~Cube();

    private:
        void MakeVBO();
        void MakeVAO();

    public:
        void Draw();

    private:
        const static size_t POINT_NR = 36;
        const PointData_t POINTS[POINT_NR] = {
            PointData_t{ .pos{-0.5f, -0.5f, -0.5f},  .texCoord{0.0f, 0.0f}, .abnormal{0.0f, 0.0f, -1.0f}},
            PointData_t{ .pos{ 0.5f, -0.5f, -0.5f},  .texCoord{1.0f, 0.0f}, .abnormal{0.0f, 0.0f, -1.0f}},
            PointData_t{ .pos{ 0.5f,  0.5f, -0.5f},  .texCoord{1.0f, 1.0f}, .abnormal{0.0f, 0.0f, -1.0f}},
            PointData_t{ .pos{ 0.5f,  0.5f, -0.5f},  .texCoord{1.0f, 1.0f}, .abnormal{0.0f, 0.0f, -1.0f}},
            PointData_t{ .pos{-0.5f,  0.5f, -0.5f},  .texCoord{0.0f, 1.0f}, .abnormal{0.0f, 0.0f, -1.0f}},
            PointData_t{ .pos{-0.5f, -0.5f, -0.5f},  .texCoord{0.0f, 0.0f}, .abnormal{0.0f, 0.0f, -1.0f}},

            PointData_t{ .pos{-0.5f, -0.5f,  0.5f},  .texCoord{0.0f, 0.0f}, .abnormal{0.0f, 0.0f, 1.0f}},
            PointData_t{ .pos{ 0.5f, -0.5f,  0.5f},  .texCoord{1.0f, 0.0f}, .abnormal{0.0f, 0.0f, 1.0f}},
            PointData_t{ .pos{ 0.5f,  0.5f,  0.5f},  .texCoord{1.0f, 1.0f}, .abnormal{0.0f, 0.0f, 1.0f}},
            PointData_t{ .pos{ 0.5f,  0.5f,  0.5f},  .texCoord{1.0f, 1.0f}, .abnormal{0.0f, 0.0f, 1.0f}},
            PointData_t{ .pos{-0.5f,  0.5f,  0.5f},  .texCoord{0.0f, 1.0f}, .abnormal{0.0f, 0.0f, 1.0f}},
            PointData_t{ .pos{-0.5f, -0.5f,  0.5f},  .texCoord{0.0f, 0.0f}, .abnormal{0.0f, 0.0f, 1.0f}},

            PointData_t{ .pos{-0.5f,  0.5f,  0.5f},  .texCoord{1.0f, 0.0f}, .abnormal{-1.0f, 0.0f, 0.0f}},
            PointData_t{ .pos{-0.5f,  0.5f, -0.5f},  .texCoord{1.0f, 1.0f}, .abnormal{-1.0f, 0.0f, 0.0f}},
            PointData_t{ .pos{-0.5f, -0.5f, -0.5f},  .texCoord{0.0f, 1.0f}, .abnormal{-1.0f, 0.0f, 0.0f}},
            PointData_t{ .pos{-0.5f, -0.5f, -0.5f},  .texCoord{0.0f, 1.0f}, .abnormal{-1.0f, 0.0f, 0.0f}},
            PointData_t{ .pos{-0.5f, -0.5f,  0.5f},  .texCoord{0.0f, 0.0f}, .abnormal{-1.0f, 0.0f, 0.0f}},
            PointData_t{ .pos{-0.5f,  0.5f,  0.5f},  .texCoord{1.0f, 0.0f}, .abnormal{-1.0f, 0.0f, 0.0f}},

            PointData_t{ .pos{0.5f,  0.5f,  0.5f},   .texCoord{1.0f, 0.0f}, .abnormal{1.0f, 0.0f, 0.0f}},
            PointData_t{ .pos{0.5f,  0.5f, -0.5f},   .texCoord{1.0f, 1.0f}, .abnormal{1.0f, 0.0f, 0.0f}},
            PointData_t{ .pos{0.5f, -0.5f, -0.5f},   .texCoord{0.0f, 1.0f}, .abnormal{1.0f, 0.0f, 0.0f}},
            PointData_t{ .pos{0.5f, -0.5f, -0.5f},   .texCoord{0.0f, 1.0f}, .abnormal{1.0f, 0.0f, 0.0f}},
            PointData_t{ .pos{0.5f, -0.5f,  0.5f},   .texCoord{0.0f, 0.0f}, .abnormal{1.0f, 0.0f, 0.0f}},
            PointData_t{ .pos{0.5f,  0.5f,  0.5f},   .texCoord{1.0f, 0.0f}, .abnormal{1.0f, 0.0f, 0.0f}},

            PointData_t{ .pos{-0.5f, -0.5f, -0.5f},  .texCoord{0.0f, 1.0f}, .abnormal{0.0f, -1.0f, 0.0f}},
            PointData_t{ .pos{ 0.5f, -0.5f, -0.5f},  .texCoord{1.0f, 1.0f}, .abnormal{0.0f, -1.0f, 0.0f}},
            PointData_t{ .pos{ 0.5f, -0.5f,  0.5f},  .texCoord{1.0f, 0.0f}, .abnormal{0.0f, -1.0f, 0.0f}},
            PointData_t{ .pos{ 0.5f, -0.5f,  0.5f},  .texCoord{1.0f, 0.0f}, .abnormal{0.0f, -1.0f, 0.0f}},
            PointData_t{ .pos{-0.5f, -0.5f,  0.5f},  .texCoord{0.0f, 0.0f}, .abnormal{0.0f, -1.0f, 0.0f}},
            PointData_t{ .pos{-0.5f, -0.5f, -0.5f},  .texCoord{0.0f, 1.0f}, .abnormal{0.0f, -1.0f, 0.0f}},

            PointData_t{ .pos{-0.5f,  0.5f, -0.5f},  .texCoord{0.0f, 1.0f}, .abnormal{0.0f, 1.0f, 0.0f}},
            PointData_t{ .pos{ 0.5f,  0.5f, -0.5f},  .texCoord{1.0f, 1.0f}, .abnormal{0.0f, 1.0f, 0.0f}},
            PointData_t{ .pos{ 0.5f,  0.5f,  0.5f},  .texCoord{1.0f, 0.0f}, .abnormal{0.0f, 1.0f, 0.0f}},
            PointData_t{ .pos{ 0.5f,  0.5f,  0.5f},  .texCoord{1.0f, 0.0f}, .abnormal{0.0f, 1.0f, 0.0f}},
            PointData_t{ .pos{-0.5f,  0.5f,  0.5f},  .texCoord{0.0f, 0.0f}, .abnormal{0.0f, 1.0f, 0.0f}},
            PointData_t{ .pos{-0.5f,  0.5f, -0.5f},  .texCoord{0.0f, 1.0f}, .abnormal{0.0f, 1.0f, 0.0f}}

            // PointData_t{.pos{-0.5f, -0.5f, -0.5f}, .abnormal{0.0f,  0.0f, -1.0f}},
            // PointData_t{.pos{ 0.5f, -0.5f, -0.5f}, .abnormal{0.0f,  0.0f, -1.0f}},
            // PointData_t{.pos{ 0.5f,  0.5f, -0.5f}, .abnormal{0.0f,  0.0f, -1.0f}},
            // PointData_t{.pos{ 0.5f,  0.5f, -0.5f}, .abnormal{0.0f,  0.0f, -1.0f}},
            // PointData_t{.pos{-0.5f,  0.5f, -0.5f}, .abnormal{0.0f,  0.0f, -1.0f}},
            // PointData_t{.pos{-0.5f, -0.5f, -0.5f}, .abnormal{0.0f,  0.0f, -1.0f}},

            // PointData_t{.pos{-0.5f, -0.5f,  0.5f}, .abnormal{ 0.0f,  0.0f,  1.0f}},
            // PointData_t{.pos{ 0.5f, -0.5f,  0.5f}, .abnormal{ 0.0f,  0.0f,  1.0f}},
            // PointData_t{.pos{ 0.5f,  0.5f,  0.5f}, .abnormal{ 0.0f,  0.0f,  1.0f}},
            // PointData_t{.pos{ 0.5f,  0.5f,  0.5f}, .abnormal{ 0.0f,  0.0f,  1.0f}},
            // PointData_t{.pos{-0.5f,  0.5f,  0.5f}, .abnormal{ 0.0f,  0.0f,  1.0f}},
            // PointData_t{.pos{-0.5f, -0.5f,  0.5f}, .abnormal{ 0.0f,  0.0f,  1.0f}},

            // PointData_t{.pos{-0.5f,  0.5f,  0.5f}, .abnormal{-1.0f,  0.0f,  0.0f}},
            // PointData_t{.pos{-0.5f,  0.5f, -0.5f}, .abnormal{-1.0f,  0.0f,  0.0f}},
            // PointData_t{.pos{-0.5f, -0.5f, -0.5f}, .abnormal{-1.0f,  0.0f,  0.0f}},
            // PointData_t{.pos{-0.5f, -0.5f, -0.5f}, .abnormal{-1.0f,  0.0f,  0.0f}},
            // PointData_t{.pos{-0.5f, -0.5f,  0.5f}, .abnormal{-1.0f,  0.0f,  0.0f}},
            // PointData_t{.pos{-0.5f,  0.5f,  0.5f}, .abnormal{-1.0f,  0.0f,  0.0f}},

            // PointData_t{.pos{0.5f,  0.5f,  0.5f},  .abnormal{1.0f,  0.0f,  0.0f}},
            // PointData_t{.pos{0.5f,  0.5f, -0.5f},  .abnormal{1.0f,  0.0f,  0.0f}},
            // PointData_t{.pos{0.5f, -0.5f, -0.5f},  .abnormal{1.0f,  0.0f,  0.0f}},
            // PointData_t{.pos{0.5f, -0.5f, -0.5f},  .abnormal{1.0f,  0.0f,  0.0f}},
            // PointData_t{.pos{0.5f, -0.5f,  0.5f},  .abnormal{1.0f,  0.0f,  0.0f}},
            // PointData_t{.pos{0.5f,  0.5f,  0.5f},  .abnormal{1.0f,  0.0f,  0.0f}},

            // PointData_t{.pos{-0.5f, -0.5f, -0.5f}, .abnormal{ 0.0f, -1.0f,  0.0f}},
            // PointData_t{.pos{ 0.5f, -0.5f, -0.5f}, .abnormal{ 0.0f, -1.0f,  0.0f}},
            // PointData_t{.pos{ 0.5f, -0.5f,  0.5f}, .abnormal{ 0.0f, -1.0f,  0.0f}},
            // PointData_t{.pos{ 0.5f, -0.5f,  0.5f}, .abnormal{ 0.0f, -1.0f,  0.0f}},
            // PointData_t{.pos{-0.5f, -0.5f,  0.5f}, .abnormal{ 0.0f, -1.0f,  0.0f}},
            // PointData_t{.pos{-0.5f, -0.5f, -0.5f}, .abnormal{ 0.0f, -1.0f,  0.0f}},

            // PointData_t{.pos{-0.5f,  0.5f, -0.5f}, .abnormal{ 0.0f,  1.0f,  0.0f}},
            // PointData_t{.pos{ 0.5f,  0.5f, -0.5f}, .abnormal{ 0.0f,  1.0f,  0.0f}},
            // PointData_t{.pos{ 0.5f,  0.5f,  0.5f}, .abnormal{ 0.0f,  1.0f,  0.0f}},
            // PointData_t{.pos{ 0.5f,  0.5f,  0.5f}, .abnormal{ 0.0f,  1.0f,  0.0f}},
            // PointData_t{.pos{-0.5f,  0.5f,  0.5f}, .abnormal{ 0.0f,  1.0f,  0.0f}},
            // PointData_t{.pos{-0.5f,  0.5f, -0.5f}, .abnormal{ 0.0f,  1.0f,  0.0f}}
        };

        const static size_t VERTEX_ATTR_NR = 3;
        const VertextAttr_t VERTEX_ATTRS[VERTEX_ATTR_NR] = {
             // PointData_t::pos
            {.index = 0, .size = sizeof(PointData_t::pos)  / sizeof(float), .type = GL_FLOAT, .normalized = GL_FALSE, .stride = sizeof(PointData_t), .pointer = NULL}, // PointData_t::pos
            {.index = 1, .size = sizeof(PointData_t::texCoord)  / sizeof(float), .type = GL_FLOAT, .normalized = GL_FALSE, .stride = sizeof(PointData_t), .pointer = reinterpret_cast<char*>(12)}, // PointData_t::texCoord
            {.index = 1, .size = sizeof(PointData_t::abnormal)  / sizeof(float), .type = GL_FLOAT, .normalized = GL_FALSE, .stride = sizeof(PointData_t), .pointer = reinterpret_cast<char*>(20)} // PointData_t::texCoord
        };

        GLuint VAO, VBO;
    };
}

#endif // DEMO_SHAPE_H__