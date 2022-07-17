#ifndef DEMO_OBJECT_H__
#define DEMO_OBJECT_H__

#include <memory>
#include "demo/imgui.h"

namespace demo
{
    namespace imgui
    {
        class CubeRenderUI;
        class TransformUI;
    }

    class Cube;
    class ShaderProgram;
    class Transform;
    class Material;
    class Lighting;

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
        void SetLightProp(const Lighting& lighting);
        void SetMaterialProp();

    private:
        Cube* m_Cube;
        Transform* m_Transform;
        Material* m_Material;
        ShaderProgram* m_ShaderProgram;

    private:
        friend class imgui::CubeRenderUI;
        imgui::CubeRenderUI* m_CubeRenderUI;
    };

    namespace imgui
    {
        class CubeRenderUI
            : public IDrawImp
        {
        public:
            explicit CubeRenderUI(CubeRender &cubeRender);
            virtual ~CubeRenderUI();

            virtual void Draw() override;

        private:
            CubeRender &m_CubeRender;
            TransformUI* m_TransformUI;
        };
    }
};

#endif