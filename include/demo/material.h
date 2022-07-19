#ifndef DEMO_MATERIAL_H__
#define DEMO_MATERIAL_H__

#include <glm/ext/vector_float3.hpp>
#include "demo/imgui.h"

namespace demo
{
    struct Material
    {
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float shininess;

        const static Material test;
    };

    namespace imgui
    {
        class MaterialUI:
            public IDrawImp,
            public AmbientSubscriber,
            public DiffuseSubscriber,
            public SpecularSubscriber,
            public ShinessSubscriber
        {
        public:
            explicit MaterialUI(Material& material);
            virtual ~MaterialUI();

            virtual void Update(AmbientPublisher*, const AmbientSubscriber::Type& ambient) override;
            virtual void Update(DiffusePublisher*, const DiffuseSubscriber::Type& diffuse) override;
            virtual void Update(SpecularPublisher*, const SpecularSubscriber::Type& specular) override;
            virtual void Update(ShinessPublisher*, const ShinessSubscriber::Type& specular) override;
            virtual void Draw() override;
        
        private:
            Material& m_Material;
            AmbientPublisher* m_AmbientPublisher;
            DiffusePublisher* m_DiffusePublisher;
            SpecularPublisher* m_SpecularPublisher;
            ShinessPublisher* m_ShinessPublisher;
        };
    };
};

#endif