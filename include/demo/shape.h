#ifndef DEMO_SHAPE_H__
#define DEMO_SHAPE_H__

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

class Cube
{
public:
    typedef struct {
        glm::vec3 pos;
        glm::vec2 texCoord;
    } PointData_t;

    Cube();
    virtual ~Cube();

private:
    void MakeVBO();
    void MakeVAO();

public:
    void DrawBuffer();

private:
    const static size_t POINT_NR = 36;
    const PointData_t POINTS[POINT_NR] = {
        PointData_t{ .pos = { -0.5f, -0.5f, -0.5f}, .texCoord = { 0.0f, 0.0f }},
        PointData_t{ .pos = { 0.5f, -0.5f, -0.5f},  .texCoord = {1.0f, 0.0f}},
        PointData_t{ .pos = { 0.5f,  0.5f, -0.5f},  .texCoord = {1.0f, 1.0f}},
        PointData_t{ .pos = { 0.5f,  0.5f, -0.5f},  .texCoord = {1.0f, 1.0f}},
        PointData_t{ .pos = { -0.5f,  0.5f, -0.5f},  .texCoord = {0.0f, 1.0f}},
        PointData_t{ .pos = { -0.5f, -0.5f, -0.5f},  .texCoord = {0.0f, 0.0f}},

        PointData_t{ .pos = { -0.5f, -0.5f,  0.5f},  .texCoord = {0.0f, 0.0f}},
        PointData_t{ .pos = { 0.5f, -0.5f,  0.5f},  .texCoord = {1.0f, 0.0f}},
        PointData_t{ .pos = { 0.5f,  0.5f,  0.5f},  .texCoord = {1.0f, 1.0f}},
        PointData_t{ .pos = { 0.5f,  0.5f,  0.5f},  .texCoord = {1.0f, 1.0f}},
        PointData_t{ .pos = { -0.5f,  0.5f,  0.5f},  .texCoord = {0.0f, 1.0f}},
        PointData_t{ .pos = { -0.5f, -0.5f,  0.5f},  .texCoord = {0.0f, 0.0f}},

        PointData_t{ .pos = { -0.5f,  0.5f,  0.5f},  .texCoord = {1.0f, 0.0f}},
        PointData_t{ .pos = { -0.5f,  0.5f, -0.5f},  .texCoord = {1.0f, 1.0f}},
        PointData_t{ .pos = { -0.5f, -0.5f, -0.5f},  .texCoord = {0.0f, 1.0f}},
        PointData_t{ .pos = { -0.5f, -0.5f, -0.5f},  .texCoord = {0.0f, 1.0f}},
        PointData_t{ .pos = { -0.5f, -0.5f,  0.5f},  .texCoord = {0.0f, 0.0f}},
        PointData_t{ .pos = { -0.5f,  0.5f,  0.5f},  .texCoord = {1.0f, 0.0f}},

        PointData_t{ .pos = { 0.5f,  0.5f,  0.5f},  .texCoord = {1.0f, 0.0f}},
        PointData_t{ .pos = { 0.5f,  0.5f, -0.5f},  .texCoord = {1.0f, 1.0f}},
        PointData_t{ .pos = { 0.5f, -0.5f, -0.5f},  .texCoord = {0.0f, 1.0f}},
        PointData_t{ .pos = { 0.5f, -0.5f, -0.5f},  .texCoord = {0.0f, 1.0f}},
        PointData_t{ .pos = { 0.5f, -0.5f,  0.5f},  .texCoord = {0.0f, 0.0f}},
        PointData_t{ .pos = { 0.5f,  0.5f,  0.5f},  .texCoord = {1.0f, 0.0f}},

        PointData_t{ .pos = { -0.5f, -0.5f, -0.5f},  .texCoord = {0.0f, 1.0f}},
        PointData_t{ .pos = { 0.5f, -0.5f, -0.5f},  .texCoord = {1.0f, 1.0f}},
        PointData_t{ .pos = { 0.5f, -0.5f,  0.5f},  .texCoord = {1.0f, 0.0f}},
        PointData_t{ .pos = { 0.5f, -0.5f,  0.5f},  .texCoord = {1.0f, 0.0f}},
        PointData_t{ .pos = { -0.5f, -0.5f,  0.5f},  .texCoord = {0.0f, 0.0f}},
        PointData_t{ .pos = { -0.5f, -0.5f, -0.5f},  .texCoord = {0.0f, 1.0f}},

        PointData_t{ .pos = { -0.5f,  0.5f, -0.5f},  .texCoord = {0.0f, 1.0f}},
        PointData_t{ .pos = { 0.5f,  0.5f, -0.5f},  .texCoord = {1.0f, 1.0f}},
        PointData_t{ .pos = { 0.5f,  0.5f,  0.5f},  .texCoord = {1.0f, 0.0f}},
        PointData_t{ .pos = { 0.5f,  0.5f,  0.5f},  .texCoord = {1.0f, 0.0f}},
        PointData_t{ .pos = { -0.5f,  0.5f,  0.5f},  .texCoord = {0.0f, 0.0f}},
        PointData_t{ .pos = { -0.5f,  0.5f, -0.5f},  .texCoord = {0.0f, 1.0f}}
    };

	GLuint VAO, VBO;
};

#endif // DEMO_SHAPE_H__