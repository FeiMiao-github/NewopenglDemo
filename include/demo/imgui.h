#ifndef DEMO_IMGUI_H__
#define DEMO_IMGUI_H__

#include "glm/ext/vector_float3.hpp"
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/matrix.hpp>

#include <list>
#include <set>
#include <memory>
#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace demo
{
    namespace imgui {
        class IDrawImp
        {
        public:
            IDrawImp() {}
            virtual ~IDrawImp() = default;
            virtual void Draw() = 0;
        };

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

        enum class SubscriberID
        {
            Position,
            Rotation,
            Scale
        };

        template <typename Subscriber>
        class Publisher;

        template <SubscriberID ID, typename DType>
        class ISubscriber
        {
        public:
            using Type = DType;
            virtual void Update(Publisher<ISubscriber>* subscriber, const DType& Pos) = 0;
        };

        template <typename Subscriber>
        class Publisher
            : public IDrawImp
        {
        public:
            Publisher(const std::string& label, const typename Subscriber::Type& init)
                : m_Label(label),
                  m_Val(init)
            {
            }

            virtual ~Publisher()
            {
            }

            virtual void AddSubscriber(Subscriber* subscriber)
            {
                if (!CheckIfExistSubscriber(subscriber))
                {
                    m_Subscriber.push_back(subscriber);
                }
            }

            virtual void RemoveSubscriber(Subscriber* subscriber)
            {
                m_Subscriber.remove(subscriber);
            }

            virtual void Draw() override
            {
                bool change = false;
                ImGui::Text("%s", m_Label.c_str());
                ImGui::SameLine();

                std::string id = "##" + m_Label;
                if (ImGui::DragFloat3(id.c_str(), &m_Val[0], 0.01f))
                {
                    change = true;
                }

                if (change)
                {
                    Update();
                }
            }

        private:
            bool CheckIfExistSubscriber(const Subscriber* subscriber)
            {
                for (auto p = m_Subscriber.begin(); p != m_Subscriber.end(); p++)
                {
                    if (*p == subscriber) return true;
                }
                return false;
            }

            void Update()
            {
                for (auto p = m_Subscriber.begin(); p != m_Subscriber.end(); p++)
                {
                    (*p)->Update(this, m_Val);
                }
            }

        private:
            std::list<Subscriber*> m_Subscriber;
            const std::string m_Label;
            typename Subscriber::Type m_Val;
        };

        using PositionSubscriber = ISubscriber<SubscriberID::Position, glm::vec3>;
        using PositionPublisher = Publisher<PositionSubscriber>;

        using RotationSubscriber = ISubscriber<SubscriberID::Rotation, glm::vec3>;
        using RotationPublisher = Publisher<RotationSubscriber>;

        using ScaleSubscriber = ISubscriber<SubscriberID::Scale, glm::vec3>;
        using ScalePublisher = Publisher<ScaleSubscriber>;
    }
}
void InitImgGui(GLFWwindow* window, const char* glsl_version);
void DrawImGui();
void DestroyImGui();

#endif // DEMO_IMGUI_H__