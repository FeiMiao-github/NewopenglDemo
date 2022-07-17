#ifndef DEMO_TEXTURE_H__
#define DEMO_TEXTURE_H__

#include <string>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class TextureException
    : public std::exception
{
protected:
    explicit TextureException(const std::string& msg) noexcept
        : _Msg(msg)
    {}

public:
    virtual ~TextureException() noexcept = default;

    virtual const char* what() const noexcept override
    {
        return _Msg.c_str();
    }

private:
    std::string _Msg;
};

class TextureLoadException
    : public TextureException
{
public:
    explicit TextureLoadException(const std::string& texture) : TextureException("load texture " + texture + " failed !") {}
    virtual ~TextureLoadException() = default;
};

class Texture
{
public:
    explicit Texture(const std::string& name);
    virtual ~Texture();
    void Use();

private:
    GLuint texture;
};

#endif // DEMO_TEXTURE_H__