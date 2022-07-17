#ifndef DEMO_LOADER_H__
#define DEMO_LOADER_H__

#include <string>

class LoaderException
    : std::exception
{
protected:
    explicit LoaderException(const std::string& msg) noexcept
        : _Msg(msg)
    {}

public:
    virtual ~LoaderException() noexcept = default;

    virtual const char* what() const noexcept override
    {
        return _Msg.c_str();
    }

private:
    std::string _Msg;
};

class LoaderOpenFileException
    : public LoaderException
{
public:
    explicit LoaderOpenFileException(const std::string& file): LoaderException("LoaderOpenFileException" + file) {}
    virtual ~LoaderOpenFileException() = default;
};

class LoaderOverscendBufferSize
    : public LoaderException
{
public:
    LoaderOverscendBufferSize() : LoaderException("LoaderOverscendBufferSize") {}
    virtual ~LoaderOverscendBufferSize() = default;
};

std::string LoadShader(const std::string &path);
std::string GetShaderFullPath(const std::string &name);
std::string GetTextureFullPath(const std::string &name);

#endif