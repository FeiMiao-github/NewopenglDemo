#include "demo/shape.h"
#include "demo/log.h"

using namespace demo;

typedef GLfloat vec2[2];
typedef GLfloat vec3[3];

typedef struct
{
	vec3 pos;
	vec3 color;
	vec2 texCoord;
} PointData_t;

typedef struct
{
	GLuint i1, i2, i3;
} TriangleIndex_t;

static void MakeTriangleVBO(PointData_t vertices[], size_t size)
{
	GLuint VBO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(PointData_t), vertices, GL_STATIC_DRAW);
}

static GLuint MakeTriangleVAO()
{
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, sizeof(PointData_t::pos)  / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(PointData_t), NULL);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, sizeof(PointData_t::color) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(PointData_t), (void*)(sizeof(PointData_t::pos)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, sizeof(PointData_t::texCoord) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(PointData_t), (void*)(sizeof(PointData_t::pos) + sizeof(PointData_t::color)));
	glEnableVertexAttribArray(2);
	return VAO;
}

static GLuint MakeTriangleEBO(TriangleIndex_t indices[], size_t size)
{
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(TriangleIndex_t), indices, GL_STATIC_DRAW);
	return EBO;
}

static GLuint MakeTriangleA()
{
	static PointData_t vertices[] = {
		{{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.5f, 0.5f}},
		{{0.5f, -0.5f, -0.5f},{1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
		{{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
		{{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.5f, 1.0f}},
		{{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
		{{-0.5f, -0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
		{{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.5f, 1.0f}}
	};

	MakeTriangleVBO(vertices, sizeof(vertices) / sizeof(PointData_t));
	return MakeTriangleVAO();
}

GLuint MakeTriangleE()
{
	TriangleIndex_t indices[] = {
		{0, 1, 2},
		{0, 2, 3},
		{4, 5, 7},
		{5, 6, 7},
		{2, 3, 6},
		{3, 6, 7},
		{0, 1, 5},
		{0, 4, 5},
		{0, 3, 7},
		{0, 4, 7},
		{1, 2, 6},
		{1, 5, 6},
	};

	MakeTriangleA();
	return MakeTriangleEBO(indices, sizeof(indices) / sizeof(TriangleIndex_t));
}

void DrawBuffer(GLuint program, GLuint triangle)
{
    glUseProgram(program);
    glBindVertexArray(triangle);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
}

const size_t Cube::POINT_NR;
const size_t Cube::VERTEX_ATTR_NR;

void Cube::MakeVBO()
{
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,
		POINT_NR * sizeof(PointData_t), reinterpret_cast<const void*>(POINTS), GL_STATIC_DRAW);
}

void Cube::MakeVAO()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	Log::debug("MakeVAO !");
	for (size_t i = 0; i < VERTEX_ATTR_NR; i++)
	{
		VertextAttr_t attr = VERTEX_ATTRS[i];
		glVertexAttribPointer(attr.index, attr.size, attr.type, attr.normalized, attr.stride, attr.pointer);
		glEnableVertexAttribArray(attr.index);
	}
}

void Cube::Draw()
{
    glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, POINT_NR);
}

Cube::Cube()
{
	MakeVBO();
	MakeVAO();
}

Cube::~Cube()
{
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
}