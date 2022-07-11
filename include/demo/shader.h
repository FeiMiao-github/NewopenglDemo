#ifndef DEMO_SHADER_H__
#define DEMO_SHADER_H__

#include <string>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderException
    : public std::exception
{
protected:
    ShaderException(const std::string& msg) noexcept
        : _Msg(msg)
    {}

public:
    virtual ~ShaderException() noexcept = default;

    virtual const char* what() const noexcept override
    {
        return _Msg.c_str();
    }

private:
    std::string _Msg;
};

class ShaderCompileFailed
    : public ShaderException
{
public:
    ShaderCompileFailed(const std::string& err) : ShaderException("Error:" + err) {}
    virtual ~ShaderCompileFailed() = default;
};

class ShaderLinkFailed
    : public ShaderException
{
public:
    ShaderLinkFailed(const std::string& err) : ShaderException("Error:" + err) {}
    virtual ~ShaderLinkFailed() = default;
};


GLuint InitProgram();

void SetProgramFloat(GLuint program, const GLchar* prop, GLfloat value);
void SetProgramMat4(GLuint program, const GLchar* prop, glm::mat4& ptr);

#endif 