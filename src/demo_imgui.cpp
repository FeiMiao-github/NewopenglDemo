#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "demo/imgui.h"

using namespace demo::imgui;

ImGuiCtx* ImGuiCtx::s_Inst = nullptr;

void InitImgGui(GLFWwindow* window, const char* glsl_version)
{
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void DrawImGui()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Hello");
    ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

    ImGuiCtx::Inst()->Draw();

    ImGui::PopItemWidth();
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void DestroyImGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

PosPublisher::PosPublisher(const std::string& label)
    : m_Pos(0.0f),
      m_Label(label)
{
    ImGuiCtx::Inst()->Add(this);
}

PosPublisher::~PosPublisher()
{
    ImGuiCtx::Inst()->Del(this);
}

void PosPublisher::AddSubscriber(IPosSubscriber *subscriber)
{
    if (!CheckIfExistSubscriber(subscriber))
    {
        m_Subscriber.push_back(subscriber);
    }
}

void PosPublisher::RemoveSubscriber(IPosSubscriber *subscriber)
{
    m_Subscriber.remove(subscriber);
}

bool PosPublisher::CheckIfExistSubscriber(IPosSubscriber* subscriber)
{
    for (auto p = m_Subscriber.begin(); p != m_Subscriber.end(); p++)
    {
        if (*p == subscriber) return true;
    }
    return false;
}

void PosPublisher::Update()
{
    for (auto p = m_Subscriber.begin(); p != m_Subscriber.end(); p++)
    {
        (*p)->UpdatePos(m_Pos);
    }
}

void PosPublisher::Draw()
{
    if (ImGui::TreeNode(m_Label.c_str()))
    {
        bool change = false;
        if (ImGui::SliderFloat3("", &m_Pos[0], -2.0f, 2.0f))
        {
            change = true;
        }

        if (change)
        {
            Update();
        }

        ImGui::TreePop();
    }
}