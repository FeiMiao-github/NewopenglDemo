#include <iostream>
#include "demo/shader.h"
#include "demo/loader.h"

static void PrintShaderCompileStatus(GLuint shader, const std::string& shaderName)
{
	char info[512] = "";
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, info);
		throw ShaderCompileFailed(shaderName + ":" + info);
	}
}

static void PrintProgramLinkStatus(GLuint program)
{
	char info[512] = "";
	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, info);
        throw ShaderLinkFailed(info);
	}
}

static GLuint InitShader(GLenum type, const std::string &shaderName)
{
    std::string fullPath = GetShaderFullPath(shaderName);
	std::string src = LoadShader(fullPath);
	std::cout << "shader src: \n" << src << '\n';
	const char* bufptr = src.c_str();
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &bufptr, NULL);
	glCompileShader(shader);
	PrintShaderCompileStatus(shader, shaderName);
	return shader;
}

GLuint InitProgram()
{
	GLuint vshader = InitShader(GL_VERTEX_SHADER, "texture_shader.vs");
	GLuint fshader = InitShader(GL_FRAGMENT_SHADER, "texture_shader.fs");

	GLuint program = glCreateProgram();

	glAttachShader(program, vshader);
	glAttachShader(program, fshader);
	glLinkProgram(program);
	PrintProgramLinkStatus(program);

	glDeleteShader(vshader);
	glDeleteShader(fshader);
	return program;
}

void SetProgramFloat(GLuint program, const GLchar* prop, GLfloat value)
{
	GLint loc = glGetUniformLocation(program, prop);
	glUniform1f(loc, value);
}

void SetProgramMat4(GLuint program, const GLchar* prop, glm::mat4& ptr)
{
	GLint loc = glGetUniformLocation(program, prop);
	glUniformMatrix4fv(loc, 1, GL_TRUE, glm::value_ptr(ptr));
}