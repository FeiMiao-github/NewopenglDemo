#ifndef DEMO_OBJECT_H__
#define DEMO_OBJECT_H__

#include "demo/shape.h"
#include "demo/shader.h"

namespace demo
{
    class Object
    {
    public:
        Object();
        virtual ~Object();

        Cube* GetCube();
        void SetCube(Cube* cube);

        ShaderProgram* GetShaderProgram();
        void SetShaderProgram(ShaderProgram* shaderProgram);

    private:
        Cube* m_Cube;
        ShaderProgram* m_ShaderProgram;
    };
};

#endif