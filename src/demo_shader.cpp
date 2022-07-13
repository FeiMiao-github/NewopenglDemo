#include <iostream>
#include <cassert>

#include <string>

#include "demo/shader.h"
#include "demo/loader.h"
#include "demo/log.h"

using namespace demo;

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

Shader::Shader(Type type, const std::string &shaderName)
{
	std::string fullPath = GetShaderFullPath(shaderName);
	std::string src = LoadShader(fullPath);
	std::cout << "shader src: \n" << src << '\n';
	const char* bufptr = src.c_str();
	GLuint shader = glCreateShader(static_cast<GLenum>(type));
	glShaderSource(shader, 1, &bufptr, NULL);
	glCompileShader(shader);
	PrintShaderCompileStatus(shader, shaderName);

	m_ID = shader;
}

Shader::~Shader()
{
	glDeleteShader(m_ID);
}

ShaderProgram::ShaderProgram(const std::initializer_list<Shader*> &list)
{
	m_ID = glCreateProgram();
	for (auto p = list.begin(); p != list.end(); p++)
	{
		Log::debug("Attach Shader: {}", (*p)->GetID());
		glAttachShader(m_ID, (*p)->GetID());
	}
	glLinkProgram(m_ID);
	PrintProgramLinkStatus(m_ID);
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_ID);
}

void ShaderProgram::SetProgramFloat(const std::string& prop, const GLfloat value)
{
	// Log::debug("SetProgramFloat: {}:{}", prop, value);
	Use();
	GLint loc = glGetUniformLocation(m_ID, prop.c_str());
	glUniform1f(loc, value);
}

void ShaderProgram::SetProgramMat4(const std::string& prop, const glm::mat4& ptr)
{
	// Log::debug("SetProgramMat4: {}:{}", prop, ptr);
	Use();
	GLint loc = glGetUniformLocation(m_ID, prop.c_str());
	glUniformMatrix4fv(loc, 1, GL_TRUE, glm::value_ptr(ptr));
}

void ShaderProgram::SetProgramFloat3(const std::string& prop, const glm::vec3& ptr)
{
	// Log::debug("SetProgramFloat3: {}:{}", prop, ptr);
	Use();
	GLuint loc = glGetUniformLocation(m_ID, prop.c_str());
	glUniform3fv(loc, 1, glm::value_ptr(ptr));
}

void ShaderProgram::Use()
{
	glUseProgram(m_ID);
}
