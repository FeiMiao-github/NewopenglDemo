#include "demo/log.h"

using namespace demo;

const Log::InitConfig Log::s_InitConfig;

std::ostream & demo::operator<<(std::ostream& o, const glm::mat4 & m)
{
    o << '\n';
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            o << m[i][j] << '\t';
        }
        o << '\n';
    }
    return o;
}

std::ostream & demo::operator<<(std::ostream& o, const glm::vec4 & v)
{
    o << '[';
    for (int i = 0; i < 4; i++)
    {
        o << v[i] << ' ';
    }
    o << ']';
    return o;
}

std::ostream & demo::operator<<(std::ostream& o, const glm::vec3 & v)
{
    o << '[';
    for (int i = 0; i < 3; i++)
    {
        o << v[i] << ' ';
    }
    o << ']';
    return o;
}
