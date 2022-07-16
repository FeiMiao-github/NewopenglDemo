#ifndef DEMO_IMGUI_H__
#define DEMO_IMGUI_H__

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/matrix.hpp>

#include <list>
#include <memory>
#include <iostream>

#include "demo/imgui/interface.h"

// template <typename Mat4>


// class FloatSlider
//     : public IDrawImp
// {
// public:
//     FloatSlider(float& v, const char* label = "")
//         : m_V(v),
//           m_Label(label)
//     {
//     }

//     virtual ~FloatSlider() {}

//     virtual void Draw()
//     {
//         if (ImGui::TreeNode(m_Label))
//         {
//             if (ImGui::SliderFloat(m_Label, &m_V, -360.0f, 360.0f))
//             {
//             }
//             ImGui::TreePop();
//         }
//     }

// private:
//     float& m_V;
//     const char *m_Label;
// };
namespace demo
{
    namespace imgui {
        class ImGuiCtx
        {
        private:
            ImGuiCtx()
            {
            }

        public:
            static ImGuiCtx* Inst()
            {
                if (s_Inst == nullptr)
                {
                    s_Inst = new ImGuiCtx;
                }
                return s_Inst;
            }

            virtual ~ImGuiCtx()
            {
                m_List.clear();
            }

            void Add(IDrawImp* inst)
            {
                m_List.push_back(inst);
            }

            void Del(IDrawImp* inst)
            {
                m_List.remove(inst);
            }

            void Draw()
            {
                for (auto p = m_List.begin(); p != m_List.end(); p++)
                {
                    (*p)->Draw();
                }
            }

        private:
            class GC
            {
            public:
                ~GC()
                {
                    delete s_Inst;
                    s_Inst = nullptr;
                }
            };

            static ImGuiCtx* s_Inst;
            std::list<IDrawImp*> m_List;
            static GC s_GC;
        };

        class IPosSubscriber
        {
        public:
            virtual void UpdatePos(const glm::vec3& Pos) = 0;
        };

        class PosPublisher
            : public IDrawImp
        {
        public:
            PosPublisher(const std::string& label);
            virtual ~PosPublisher();

            void AddSubscriber(IPosSubscriber* subscriber);
            void RemoveSubscriber(IPosSubscriber* subscriber);

            virtual void Draw();

        private:
            bool CheckIfExistSubscriber(IPosSubscriber* subscriber);
            void Update();

        private:
            std::list<IPosSubscriber*> m_Subscriber;
            glm::vec3 m_Pos;
            const std::string m_Label;
        };
        
    }
}
void InitImgGui(GLFWwindow* window, const char* glsl_version);
void DrawImGui();
void DestroyImGui();

#endif // DEMO_IMGUI_H__