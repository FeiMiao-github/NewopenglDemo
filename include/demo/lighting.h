#ifndef DEMO_LIGHTING_H__
#define DEMO_LIGHTING_H__

#include "demo/object.h"
#include "demo/shader.h"
#include "demo/shape.h"
#include "demo/imgui.h"
#include "glm/ext/vector_float3.hpp"
#include "glm/ext/vector_float4.hpp"

namespace demo
{
    class Lighting
        : public demo::RenderTarget, imgui::IPosSubscriber
    {
    public:
        Lighting();
        virtual ~Lighting();
        
        virtual void Draw() override;
        const glm::vec4 Color() const;
        const glm::vec3 Pos() const;

        virtual void UpdatePos(const glm::vec3& Pos) override;
    
    private:
        void SetColor(const glm::vec4& color);
        void SetPos(const glm::vec3& pos);

    private:
        Cube* m_Cube;
        ShaderProgram* m_ShaderProgram;
        LocalCoordination* m_Model;

        glm::vec4 m_Color;
        glm::vec3 m_Pos;
        imgui::PosPublisher* m_PosPublisher;
    };
}

#endif