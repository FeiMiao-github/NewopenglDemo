#ifndef DEMO_IMGUI_H__
#define DEMO_IMGUI_H__

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/matrix.hpp>

#include <list>
#include <memory>
#include <iostream>

class IDrawImp
{
public:
    IDrawImp() {}
    virtual ~IDrawImp() = default;

    virtual void Draw() = 0;
};

class Mat4Gui
    : public IDrawImp
{

public:
    Mat4Gui(glm::mat4 &m4, const char* label)
        : m_Mat(m4),
          m_Label(label)
    {
    }

    virtual ~Mat4Gui() {}

    virtual void Draw() override
    {
        ImGui::PushID(m_Label);

        if (ImGui::TreeNode(m_Label))
        {
            if (ImGui::BeginTable(m_Label, 4, 1))
            {
                for (int row = 0; row < 4; row++)
                {
                    ImGui::TableNextRow();
                    for (int column = 0; column < 4; column++)
                    {
                        ImGui::TableSetColumnIndex(column);
                        ImGui::Text("%.5f", m_Mat[row][column]);
                    }
                }
                ImGui::EndTable();
            }
            ImGui::TreePop();
        }

        ImGui::PopID();
    }

private:
    glm::mat4& m_Mat;
    const char *m_Label;
};

class FloatSlider
    : public IDrawImp
{
public:
    FloatSlider(float& v, const char* label = "")
        : m_V(v),
          m_Label(label)
    {
    }

    virtual ~FloatSlider() {}

    virtual void Draw()
    {
        if (ImGui::TreeNode(m_Label))
        {
            if (ImGui::SliderFloat(m_Label, &m_V, -360.0f, 360.0f))
            {
            }
            ImGui::TreePop();
        }
    }

private:
    float& m_V;
    const char *m_Label;
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

void InitImgGui(GLFWwindow* window, const char* glsl_version);
void DrawImGui();
void DestroyImGui();

#endif // DEMO_IMGUI_H__