#ifndef DEMO_SHADER_H__
#define DEMO_SHADER_H__

#include <initializer_list>
#include <string>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace demo
{
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

    class Shader
    {
    public:
        enum class Type : unsigned int
        {
            VERTEX_SHADER = GL_VERTEX_SHADER,
            FRAGMENT_SHADER = GL_FRAGMENT_SHADER
        };
        Shader(Type type, const std::string &shaderName);
        virtual ~Shader();

        GLuint GetID()
        {
            return m_ID;
        }

    private:
        GLuint m_ID;
    };

    class VertexShader:
        public Shader
    {
    public:
        VertexShader(const std::string& name)
            : Shader(Type::VERTEX_SHADER, name)
        {
        }
        virtual ~VertexShader() = default;
    };

    class FragmentShader:
        public Shader
    {
    public:
        FragmentShader(const std::string& name)
            : Shader(Type::FRAGMENT_SHADER, name)
        {
        }

        virtual ~FragmentShader() = default;
    };

    class ShaderProgram
    {
    public:
        ShaderProgram(const std::initializer_list<Shader*>& list);
        ~ShaderProgram();

        GLuint GetID()
        {
            return m_ID;
        }

        void SetProgramFloat(const std::string& prop, const GLfloat value);
        void SetProgramMat4(const std::string& prop, const glm::mat4& ptr);
        void SetProgramFloat3(const std::string& prop, const glm::vec3& ptr);

        void Use();

    private:
        GLuint m_ID;
    };
}

#endif 