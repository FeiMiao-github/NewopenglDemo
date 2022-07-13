#include "demo/object.h"
#include "demo/shader.h"
#include <cstddef>

using namespace demo;

Object::Object()
    : m_Cube(nullptr),
      m_ShaderProgram(nullptr)
{
}

Object::~Object()
{
    delete m_Cube;
    delete m_ShaderProgram;
}

Cube* Object::GetCube()
{
    return m_Cube;
}

void Object::SetCube(Cube *cube)
{
    if (cube == nullptr)
    {
        return;
    }

    if (m_Cube != nullptr)
    {
        delete m_Cube;
    }

    m_Cube = new Cube(*cube);
}

ShaderProgram* Object::GetShaderProgram()
{
    return m_ShaderProgram;
}

void Object::SetShaderProgram(ShaderProgram* shaderProgram)
{
    if (shaderProgram == nullptr)
    {
        return;
    }

    if (m_ShaderProgram != nullptr)
    {
        delete m_ShaderProgram;
    }

    m_ShaderProgram = new ShaderProgram(*shaderProgram);
}