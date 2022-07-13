#ifndef DEMO_OBJECT_H__
#define DEMO_OBJECT_H__

#include "demo/shape.h"
#include "demo/shader.h"
#include "demo/context.h"

namespace demo
{
    class RenderTarget
    {
    public:
        RenderTarget(Context& ctx);
        virtual ~RenderTarget();
        virtual void Draw() = 0;

    //     Cube* GetCube();
    //     void SetCube(Cube* cube);

    //     ShaderProgram* GetShaderProgram();
    //     void SetShaderProgram(ShaderProgram* shaderProgram);

    // private:
    //     Cube* m_Cube;
    //     ShaderProgram* m_ShaderProgram;
    protected:
        Context& m_Context;
    };

    class CubeRender
        : public RenderTarget
    {
    public:
        CubeRender(Context& ctx);
        virtual ~CubeRender();

        virtual void Draw() override;

    private:
        Cube* m_Cube;
        LocalCoordination* m_Model;
        ShaderProgram* m_ShaderProgram;
    };
};

#endif