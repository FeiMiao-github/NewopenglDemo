#include <iostream>
#include <cassert>
#include <string>

#include <loguru/loguru.hpp>

#include "demo/shader.h"
#include "demo/loader.h"
#include "demo/log.h"

using namespace demo;

static void PrintShaderCompileStatus(GLuint shader, const std::string& shaderName)
{
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char info[512] = "";
		glGetShaderInfoLog(shader, 512, NULL, info);
		throw ShaderCompileFailed(shaderName + ":" + info);
	}
}

static void PrintProgramLinkStatus(GLuint program)
{
	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		char info[512] = "";
		glGetProgramInfoLog(program, 512, NULL, info);
        throw ShaderLinkFailed(info);
	}
}

Shader::Shader(Type type, const std::string &shaderName)
{
	std::string fullPath = GetShaderFullPath(shaderName);
	std::string src = LoadShader(fullPath);
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
		LOG_S(INFO) << "Attach Shader:" << (*p)->GetID();
		glAttachShader(m_ID, (*p)->GetID());
	}
	glLinkProgram(m_ID);
	PrintProgramLinkStatus(m_ID);
}

ShaderProgram::ShaderProgram(const std::string& vertex, const std::string& fragment)
{
	Shader* vertexShader = new VertexShader(vertex.c_str());
    Shader* fragmentShader = new FragmentShader(fragment.c_str());
	
	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexShader->GetID());
	glAttachShader(m_ID, fragmentShader->GetID());
	glLinkProgram(m_ID);
	PrintProgramLinkStatus(m_ID);

	delete fragmentShader;
	delete vertexShader;
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_ID);
}

GLuint ShaderProgram::GetID()
{
	return m_ID;
}

void ShaderProgram::AssertUniformLocation(GLint loc, const std::string& prop)
{
	// if (loc == -1)
	// {
	// 	std::string errmsg = "set ";
	// 	errmsg.append(prop);
	// 	errmsg.append(" error !");
	// 	throw ShaderUniformNotExist(errmsg);
	// }
}

void ShaderProgram::SetProgram(const std::string& prop, const GLfloat value)
{
	Use();
	GLint loc = glGetUniformLocation(m_ID, prop.c_str());
	AssertUniformLocation(loc, prop);
	// Log::debug("SetProgramFloat: {}:{}", prop, value, loc);
	glUniform1f(loc, value);
}

void ShaderProgram::SetProgram(const std::string& prop, const glm::mat4& ptr)
{
	Use();
	GLint loc = glGetUniformLocation(m_ID, prop.c_str());
	AssertUniformLocation(loc, prop);
	// Log::debug("SetProgramMat4: {}:{}", prop, ptr, loc);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(ptr));
}

void ShaderProgram::SetProgram(const std::string& prop, const glm::vec3& ptr)
{
	Use();
	GLint loc = glGetUniformLocation(m_ID, prop.c_str());
	AssertUniformLocation(loc, prop);
	// Log::debug("SetProgramFloat3: {}:{}", prop, ptr, loc);
	glUniform3fv(loc, 1, glm::value_ptr(ptr));
}

void ShaderProgram::SetProgram(const std::string& prop, const glm::vec4& ptr)
{
	Use();
	GLint loc = glGetUniformLocation(m_ID, prop.c_str());
	AssertUniformLocation(loc, prop);
	Log::debug("SetProgramFloat4: {}:{}", prop, ptr, loc);
	glUniform4fv(loc, 1, glm::value_ptr(ptr));
}

void ShaderProgram::Use()
{
	glUseProgram(m_ID);
}
