#ifndef DEMO_LIGHTING_H__
#define DEMO_LIGHTING_H__

#include "demo/object.h"
#include "demo/shader.h"
#include "demo/shape.h"
#include "demo/imgui.h"
#include "demo/transform.h"
#include "glm/ext/vector_float3.hpp"

namespace demo
{
    namespace imgui
    {
        class LightingUI;
    }

    class Lighting
        : public RenderTarget
    {
    public:
        Lighting();
        virtual ~Lighting();
        
        virtual void Draw() override;

        const glm::vec3 Pos() const;
        const glm::vec3 Rotation() const;
        const glm::vec3 Scale() const;

        const glm::vec3 Color() const;
        const glm::vec3 AmbientColor() const;
        const glm::vec3 DiffuseColor() const;
        const glm::vec3 SpecularColor() const;

        void SetAmbient(const glm::vec3 &ambient);
        void SetDiffuse(const glm::vec3 &diffuse);
        void SetSpecular(const glm::vec3 &specular);

    private:
        void SetPos(const glm::vec3& pos);
        void SetRotation(const glm::vec3& rotation);
        void SetScale(const glm::vec3& scale);

        void SetColor(const glm::vec3& color);

    private:
        Cube* m_Cube;
        ShaderProgram* m_ShaderProgram;
        Transform* m_Transform;

        glm::vec3 m_Color;
        glm::vec3 m_AmbientColor;
        glm::vec3 m_DiffuseColor;
        glm::vec3 m_SpecularColor;

        glm::vec3 m_Diffuse;
        glm::vec3 m_Ambient;
        glm::vec3 m_Specular;

    private:
        friend class imgui::LightingUI;
        
        imgui::LightingUI* m_LightingUI;
    };

    namespace imgui
    {
        class LightingUI:
            public IDrawImp
        {
        public:
            explicit LightingUI(Lighting& lighting);
            virtual ~LightingUI();

            virtual void Draw() override;
        
        private:
            Lighting& m_Lighting;
            TransformUI* m_TransformUI;
        };
    }
}

#endif