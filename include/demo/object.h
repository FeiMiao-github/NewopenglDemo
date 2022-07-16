#ifndef DEMO_OBJECT_H__
#define DEMO_OBJECT_H__

#include "demo/coordination.h"
#include "demo/shape.h"
#include "demo/shader.h"

namespace demo
{
    class RenderTarget
    {
    public:
        RenderTarget();
        virtual ~RenderTarget();
        virtual void Draw() = 0;
    };

    class CubeRender
        : public RenderTarget
    {
    public:
        CubeRender();
        virtual ~CubeRender();

        virtual void Draw() override;

    private:
        Cube* m_Cube;
        LocalCoordination* m_Model;
        ShaderProgram* m_ShaderProgram;
    };
};

#endif